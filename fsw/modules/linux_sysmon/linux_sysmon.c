/***********************************************************************
 *  Copyright (c) 2017, United States government as represented by the
 *  administrator of the National Aeronautics and Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 *
 *  \file linux_sysmon.c
 *
 ***********************************************************************/

/*
 * NOTE: This relies on the Linux Kernel stats via the /proc filesystem.
 * Documented here: https://man7.org/linux/man-pages/man5/proc_stat.5.html
 */

/************************************************************************
 * Includes
 ************************************************************************/

#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

#include "cfe_psp.h"
#include "cfe_psp_module.h"
#include "osapi-clock.h"

#include "iodriver_impl.h"
#include "iodriver_analog_io.h"

/********************************************************************
 * Local Defines
 ********************************************************************/

#define LINUX_SYSMON_MAX_CPUS  32
#define LINUX_SYSMON_RING_SIZE 4     /* keep as power of 2 */
#define LINUX_SYSMON_PERIOD_MS 10000 /* this is the nominal period between samples */

#ifdef DEBUG_BUILD
#define LINUX_SYSMON_DEBUG(...) OS_printf(__VA_ARGS__)
#else
#define LINUX_SYSMON_DEBUG(...)
#endif

/********************************************************************
 * Local Type Definitions
 ********************************************************************/

/* these are the columns in the /proc/stat info */
/* there may be more slots than this.  This is only the ones we care about here. */
enum
{
    LINUX_PROC_CPUNUM_SLOT = 0,
    LINUX_PROC_USER_SLOT   = 1,
    LINUX_PROC_SYSTEM_SLOT = 3,
    LINUX_PROC_IDLE_SLOT   = 4,
    LINUX_PROC_NUM_SLOTS   = 5
};

enum
{
    LINUX_SYSMON_AGGREGATE_SUBSYS,
    LINUX_SYSMON_CPULOAD_SUBSYS,
    LINUX_SYSMON_PERCPU_USER_SUBSYS,
    LINUX_SYSMON_PERCPU_KERNEL_SUBSYS,
    LINUX_SYSMON_MAX_SUBSYS
};

enum
{
    LINUX_SYSMON_AGGR_CPULOAD_SUBCH,
    LINUX_SYSMON_AGGR_CPUUSER_SUBCH,
    LINUX_SYSMON_AGGR_CPUKERNEL_SUBCH,
    LINUX_SYSMON_AGGR_MAX_SUBCH
};

typedef struct linux_sysmon_statinfo_ticks
{
    unsigned long user_ticks;
    unsigned long sys_ticks;
    unsigned long idle_ticks;
} linux_sysmon_statinfo_ticks_t;

/* a ring buffer to retain the previous samples */
typedef struct linux_sysmon_statinfo_buffer
{
    linux_sysmon_statinfo_ticks_t sample[LINUX_SYSMON_RING_SIZE];
} linux_sysmon_statinfo_buffer_t;

/* a ring buffer to retain the previous clock snapshots */
typedef struct linux_sysmon_time_buffer
{
    OS_time_t sample[LINUX_SYSMON_RING_SIZE];
} linux_sysmon_time_buffer_t;

typedef struct linux_sysmon_statinfo_state
{
    volatile bool     is_running;
    volatile bool     should_run;
    volatile uint32_t num_samples;

    uint8_t   num_cpus;
    pthread_t task_id;
    int       stat_fd;
    long      sys_hz;

    linux_sysmon_time_buffer_t     sample_time;
    linux_sysmon_statinfo_buffer_t aggregate;
    linux_sysmon_statinfo_buffer_t per_core[LINUX_SYSMON_MAX_CPUS];
} linux_sysmon_statinfo_state_t;

typedef struct linux_sysmon_state
{
    uint32_t                      local_module_id;
    linux_sysmon_statinfo_state_t statinfo;
} linux_sysmon_state_t;

/********************************************************************
 * Local Function Prototypes
 ********************************************************************/

static void   *linux_sysmon_Task(void *arg);
static int32_t linux_sysmon_Start(linux_sysmon_statinfo_state_t *state);
static int32_t linux_sysmon_Stop(linux_sysmon_statinfo_state_t *state);
static void    linux_sysmon_Init(uint32_t local_module_id);

/* Function that starts up linux_sysmon driver. */
static int32_t
linux_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId, CFE_PSP_IODriver_Arg_t Arg);

/********************************************************************
 * Global Data
 ********************************************************************/

/* the global state structure (singleton) */
linux_sysmon_state_t linux_sysmon_global;

/* linux_sysmon device command that is called by iodriver to start up linux_sysmon */
CFE_PSP_IODriver_API_t linux_sysmon_DevApi = { .DeviceCommand = linux_sysmon_DevCmd };

CFE_PSP_MODULE_DECLARE_IODEVICEDRIVER(linux_sysmon);

static const char *linux_sysmon_subsystem_names[LINUX_SYSMON_MAX_SUBSYS] = {
    [LINUX_SYSMON_AGGREGATE_SUBSYS]     = "aggregate",
    [LINUX_SYSMON_CPULOAD_SUBSYS]       = "per-cpu",
    [LINUX_SYSMON_PERCPU_USER_SUBSYS]   = "per-cpu-user",
    [LINUX_SYSMON_PERCPU_KERNEL_SUBSYS] = "per-cpu-kernel"
};

static const char *linux_sysmon_aggregate_subchannel_names[LINUX_SYSMON_AGGR_MAX_SUBCH] = {
    [LINUX_SYSMON_AGGR_CPULOAD_SUBCH]   = "cpu-load",
    [LINUX_SYSMON_AGGR_CPUUSER_SUBCH]   = "cpu-user",
    [LINUX_SYSMON_AGGR_CPUKERNEL_SUBCH] = "cpu-kernel"
};

/***********************************************************************
 * Helper Functions
 ********************************************************************/

/* -----------------------------------
 * Get the tick buffer corresponding to a sample number
 * ----------------------------------- */
static linux_sysmon_statinfo_ticks_t *linux_sysmon_get_buf(uint32_t sample_count, linux_sysmon_statinfo_buffer_t *buf_p)
{
    return &buf_p->sample[sample_count & (LINUX_SYSMON_RING_SIZE - 1)];
}

/* -----------------------------------
 * Get the time buffer corresponding to a sample number
 * ----------------------------------- */
static OS_time_t *linux_sysmon_get_time(uint32_t sample_count, linux_sysmon_time_buffer_t *buf_p)
{
    return &buf_p->sample[sample_count & (LINUX_SYSMON_RING_SIZE - 1)];
}

/* -----------------------------------
 * Get the idle tick difference between two samples
 * ----------------------------------- */
static unsigned long linux_sysmon_get_idle_ticks(linux_sysmon_statinfo_ticks_t *latest_p,
                                                 linux_sysmon_statinfo_ticks_t *prev_p)
{
    return (latest_p->idle_ticks - prev_p->idle_ticks);
}

/* -----------------------------------
 * Get the user tick difference between two samples
 * ----------------------------------- */
static unsigned long linux_sysmon_get_user_ticks(linux_sysmon_statinfo_ticks_t *latest_p,
                                                 linux_sysmon_statinfo_ticks_t *prev_p)
{
    return (latest_p->user_ticks - prev_p->user_ticks);
}

/* -----------------------------------
 * Get the system tick difference between two samples
 * ----------------------------------- */
static unsigned long linux_sysmon_get_sys_ticks(linux_sysmon_statinfo_ticks_t *latest_p,
                                                linux_sysmon_statinfo_ticks_t *prev_p)
{
    return (latest_p->sys_ticks - prev_p->sys_ticks);
}

/* -----------------------------------
 * Calculate the rate of increase for a tick count over the last sample period
 * ----------------------------------- */
static int64_t linux_sysmon_calc_tick_rate(uint32_t                        sample_id,
                                           linux_sysmon_time_buffer_t     *time_buf,
                                           linux_sysmon_statinfo_buffer_t *tick_buf,
                                           unsigned long (*get_ticks_fn)(linux_sysmon_statinfo_ticks_t *,
                                                                         linux_sysmon_statinfo_ticks_t *))
{
    linux_sysmon_statinfo_ticks_t *latest_p;
    linux_sysmon_statinfo_ticks_t *prev_p;
    OS_time_t                      latest_tm;
    OS_time_t                      prev_tm;
    int64_t                        elapsed_ms;
    int64_t                        result_rate;

    latest_tm  = *(linux_sysmon_get_time(sample_id, time_buf));
    prev_tm    = *(linux_sysmon_get_time(sample_id - 1, time_buf));
    elapsed_ms = OS_TimeGetTotalMilliseconds(OS_TimeSubtract(latest_tm, prev_tm));

    if (elapsed_ms == 0)
    {
        /* invalid sample data - do not divide by 0 */
        result_rate = 0;
    }
    else
    {
        latest_p = linux_sysmon_get_buf(sample_id, tick_buf);
        prev_p   = linux_sysmon_get_buf(sample_id - 1, tick_buf);

        /*
         * The resulting units for this calculation will be "jiffy increase per
         * sampling interval" for the respective counter, but normalized/adjusted from
         * the real/measured time between samples.
         * This compensates for inconsistencies in the sampling task scheduling.
         */
        result_rate  = get_ticks_fn(latest_p, prev_p);
        result_rate *= LINUX_SYSMON_PERIOD_MS;
        result_rate /= elapsed_ms;
    }

    return result_rate;
}

/* -----------------------------------
 * Parses a single "cpu" line from /proc/stat
 * ----------------------------------- */
static void
linux_sysmon_read_cpuuse_line(const char *line_data, unsigned long *cpu_num, linux_sysmon_statinfo_ticks_t *output)
{
    unsigned long  value;
    const char    *val_end;
    int            val_count;
    unsigned long *output_p;

    unsigned long *const OUTPUT_MAP[LINUX_PROC_NUM_SLOTS] = {
        [LINUX_PROC_CPUNUM_SLOT] = cpu_num,
        [LINUX_PROC_USER_SLOT]   = &output->user_ticks,
        [LINUX_PROC_SYSTEM_SLOT] = &output->sys_ticks,
        [LINUX_PROC_IDLE_SLOT]   = &output->idle_ticks,
    };

    *cpu_num = 0;
    memset(output, 0, sizeof(*output));

    /* the initial line data should point at the cpu number,
     * or blank for the aggregate statistics (the first line of stat output) */
    val_count = 0;
    if (isblank((int)(*line_data)))
    {
        /* no CPU number -- means aggregate */
        ++val_count;
        ++line_data;
    }

    /*
     * each "cpu" line contains the cpu number followed by up to 10 numeric values,
     * depending on the kernel version and config.  Not all is relevent to cFE.
     * The important info is in the first few values.
     */
    while (val_count < LINUX_PROC_NUM_SLOTS && *line_data != 0)
    {
        while (isblank((int)(*line_data)))
        {
            ++line_data;
        }
        value = strtoul(line_data, (char **)&val_end, 10);
        if (val_end == line_data)
        {
            /* not a number, stop here */
            break;
        }

        output_p = OUTPUT_MAP[val_count];
        if (output_p != NULL)
        {
            /* make it so real samples are always nonzero, 0 indicates unknown data */
            /* note for tick counts we always take the diff between two samples, so this +1 cancels out */
            *output_p = 1 + value;
        }

        line_data = val_end;
        ++val_count;
    }
}

/* -----------------------------------
 * Read the /proc/stat file and store values to buffer
 * ----------------------------------- */
static void linux_sysmon_update_stat(linux_sysmon_statinfo_state_t *state)
{
    unsigned long                 highest_cpu_num;
    unsigned long                 cpu_num;
    linux_sysmon_statinfo_ticks_t sample_temp;
    char                          line_data[256];
    size_t                        line_size;
    ssize_t                       line_rdsz;
    char                         *eol_p;
    off_t                         lseek_ret;
    uint32_t                      next_count;
    bool                          at_line_start;

    linux_sysmon_statinfo_ticks_t *core_p;

    line_size       = 0;
    highest_cpu_num = 0;
    at_line_start   = true;
    next_count      = 1 + state->num_samples;

    /* Sample the clock at the start */
    /* it does not really matter if its not perfectly correlated */
    CFE_PSP_GetTime(linux_sysmon_get_time(next_count, &state->sample_time));

    /* Reset to beginning of file to re-read it */
    lseek_ret = lseek(state->stat_fd, 0, SEEK_SET);

    if (lseek_ret == -1)
    {
        /* this should never happen */
        OS_printf("CFE_PSP(linux_sysmon): lseek error: %s\n", strerror(errno));
        state->should_run = false;
    }

    while (state->should_run)
    {
        line_rdsz = read(state->stat_fd, &line_data[line_size], sizeof(line_data) - line_size);
        if (line_rdsz < 0)
        {
            /* error (not expected), stop reading */
            break;
        }

        if (line_rdsz == 0)
        {
            /* EOF, stop reading.  This is a "good" result. */
            state->num_cpus    = highest_cpu_num;
            state->num_samples = next_count;
            break;
        }

        /* check for newline char */
        eol_p      = memchr(&line_data[line_size], '\n', line_rdsz);
        line_size += line_rdsz;

        while (eol_p != NULL)
        {
            *eol_p = 0;
            ++eol_p;

            if (at_line_start && strncmp("cpu", line_data, 3) == 0)
            {
                /* this should set all outputs to be >= 0 */
                linux_sysmon_read_cpuuse_line(&line_data[3], &cpu_num, &sample_temp);

                LINUX_SYSMON_DEBUG("CFE_PSP(linux_sysmon): CPU%ld user=%ld sys=%ld idle=%ld\n",
                                   cpu_num,
                                   sample_temp.user_ticks,
                                   sample_temp.sys_ticks,
                                   sample_temp.idle_ticks);

                if (cpu_num == 0)
                {
                    core_p = linux_sysmon_get_buf(next_count, &state->aggregate);
                }
                else if (cpu_num <= LINUX_SYSMON_MAX_CPUS)
                {
                    core_p = linux_sysmon_get_buf(next_count, &state->per_core[cpu_num - 1]);
                }
                else
                {
                    core_p = NULL;
                }

                if (cpu_num > highest_cpu_num)
                {
                    highest_cpu_num = cpu_num;
                }

                if (core_p != NULL)
                {
                    *core_p = sample_temp;
                }
            }

            at_line_start = true;
            line_rdsz     = eol_p - &line_data[0];
            if (line_rdsz < line_size)
            {
                memmove(line_data, eol_p, line_size - line_rdsz);
                line_size -= line_rdsz;
            }
            else
            {
                line_size = 0;
            }

            eol_p = memchr(line_data, '\n', line_size);
        }

        if (line_size >= sizeof(line_data))
        {
            /* This is a long line - drop it (dont care about this stat) */
            at_line_start = false;
            line_size     = 0;
        }
    }
}

/* -----------------------------------
 * Helper task to periodically read the /proc/stat file
 * ----------------------------------- */
static void *linux_sysmon_Task(void *arg)
{
    linux_sysmon_statinfo_state_t *state = arg;

    /* This first pass is to just prime the data structure with initial info */
    /* This will cause two samples to be populated right from the start */
    linux_sysmon_update_stat(state);
    OS_TaskDelay(2000 / state->sys_hz); /* just to get a nonzero time between samples */

    while (state->should_run)
    {
        linux_sysmon_update_stat(state);

        /* this does not need to be scheduled accurately */
        OS_TaskDelay(LINUX_SYSMON_PERIOD_MS);
    }

    return NULL;
}

/* -----------------------------------
 * Convert a "jiffies per sampling period" rate into normalized 24-bit fraction
 * ----------------------------------- */
static CFE_PSP_IODriver_AdcCode_t linux_sysmon_normalize(int64_t load_units, int64_t total_units)
{
    int64_t result;

    /* this should convert to a 24-bit value */
    if (total_units == 0)
    {
        /* do not divide by 0 */
        result = 0;
    }
    else
    {
        result = (0xFFFFFF * load_units) / total_units;

        /* cap the output at the ADC code range (24-bit) */
        if (result < 0)
        {
            /* min scale, 0% load */
            result = 0;
        }
        else if (result > 0xFFFFFF)
        {
            /* max scale, 100% load */
            result = 0xFFFFFF;
        }
    }

    return (CFE_PSP_IODriver_AdcCode_t)result;
}

/* -----------------------------------
 * Get the Per-CPU load (non-idle time) in normalized form
 * ----------------------------------- */
static CFE_PSP_IODriver_AdcCode_t linux_sysmon_get_single_core_nonidle_load(linux_sysmon_statinfo_state_t *state,
                                                                            uint32_t                       core_num)
{
    int64_t idle_tick_rate;
    int64_t max_jiffies;

    idle_tick_rate = linux_sysmon_calc_tick_rate(state->num_samples,
                                                 &state->sample_time,
                                                 &state->per_core[core_num],
                                                 linux_sysmon_get_idle_ticks);
    max_jiffies    = (LINUX_SYSMON_PERIOD_MS * state->sys_hz) / 1000;

    /* this needs to convert from "idle units" to "load units" (inverse) */
    return linux_sysmon_normalize(max_jiffies - idle_tick_rate, max_jiffies);
}

/* -----------------------------------
 * Get the Per-CPU User load in normalized form
 * ----------------------------------- */
static CFE_PSP_IODriver_AdcCode_t linux_sysmon_get_single_core_user_load(linux_sysmon_statinfo_state_t *state,
                                                                         uint32_t                       core_num)
{
    int64_t user_tick_rate;
    int64_t max_jiffies;

    user_tick_rate = linux_sysmon_calc_tick_rate(state->num_samples,
                                                 &state->sample_time,
                                                 &state->per_core[core_num],
                                                 linux_sysmon_get_user_ticks);
    max_jiffies    = (LINUX_SYSMON_PERIOD_MS * state->sys_hz) / 1000;

    return linux_sysmon_normalize(user_tick_rate, max_jiffies);
}

/* -----------------------------------
 * Get the Per-CPU System/Kernel load in normalized form
 * ----------------------------------- */
static CFE_PSP_IODriver_AdcCode_t linux_sysmon_get_single_core_system_load(linux_sysmon_statinfo_state_t *state,
                                                                           uint32_t                       core_num)
{
    int64_t user_tick_rate;
    int64_t max_jiffies;

    user_tick_rate = linux_sysmon_calc_tick_rate(state->num_samples,
                                                 &state->sample_time,
                                                 &state->per_core[core_num],
                                                 linux_sysmon_get_sys_ticks);
    max_jiffies    = (LINUX_SYSMON_PERIOD_MS * state->sys_hz) / 1000;

    return linux_sysmon_normalize(user_tick_rate, max_jiffies);
}

/* -----------------------------------
 * Get the aggregate/overall CPU load (non-idle time) in normalized form
 * ----------------------------------- */
static CFE_PSP_IODriver_AdcCode_t linux_sysmon_get_aggregate_load(linux_sysmon_statinfo_state_t *state)
{
    int64_t idle_tick_rate;
    int64_t max_jiffies;

    idle_tick_rate = linux_sysmon_calc_tick_rate(state->num_samples,
                                                 &state->sample_time,
                                                 &state->aggregate,
                                                 linux_sysmon_get_idle_ticks);

    /* the main diff here is that this is jiffies across all CPUs.  So if the SYS_HZ is 100
     * and there are 4 CPUs, then there are 400 total jiffies per sec, not 100 */
    max_jiffies = (LINUX_SYSMON_PERIOD_MS * state->sys_hz * state->num_cpus) / 1000;

    /* this needs to convert from "idle units" to "load units" (inverse) */
    return linux_sysmon_normalize(max_jiffies - idle_tick_rate, max_jiffies);
}

/***********************************************************************
 * Global Functions
 ********************************************************************/

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * linux_sysmon_Init()
 * ------------------------------------------------------
 *  Sets up the initial state
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void linux_sysmon_Init(uint32_t local_module_id)
{
    memset(&linux_sysmon_global, 0, sizeof(linux_sysmon_global));

    linux_sysmon_global.local_module_id = local_module_id;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * linux_sysmon_Start()
 * ------------------------------------------------------
 *  Starts the cpu load watcher function
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int32_t linux_sysmon_Start(linux_sysmon_statinfo_state_t *state)
{
    int32_t StatusCode;
    int32_t DelayCount;

    DelayCount = 0;
    if (state->is_running)
    {
        /* already running, nothing to do */
        StatusCode = CFE_PSP_SUCCESS;
    }
    else
    {
        /* start clean */
        memset(state, 0, sizeof(*state));
        StatusCode = CFE_PSP_ERROR;

        /* determine the tick rate -- this is the unit for all counters in /proc/stat */
        state->sys_hz  = sysconf(_SC_CLK_TCK);
        state->stat_fd = open("/proc/stat", O_RDONLY);
        if (state->stat_fd < 0)
        {
            perror("open(/proc/stat)");
        }
        else
        {
            state->should_run = true;
            if (pthread_create(&state->task_id, NULL, linux_sysmon_Task, state) < 0)
            {
                perror("pthread_create()");

                /* Clean up */
                state->should_run = false;
                close(state->stat_fd);
            }
            else
            {
                /* wait for the "num_cpus" to become nonzero, this should be
                 * initialized in the first sample taken by the worker task */
                while (state->num_cpus == 0 && DelayCount < 100000000 /*jphfix*/)
                {
                    ++DelayCount;
                    OS_TaskDelay(10);
                }

                if (state->num_cpus == 0)
                {
                    OS_printf("CFE_PSP(Linux_SysMon): Failed to detect number of CPUs\n");

                    /* Clean up */
                    state->should_run = false;
                    pthread_cancel(state->task_id);
                    pthread_join(state->task_id, NULL);
                    close(state->stat_fd);
                }
                else
                {
                    OS_printf("CFE_PSP(Linux_SysMon): Started CPU utilization monitoring on %u CPU(s)\n",
                              (unsigned int)state->num_cpus);

                    StatusCode        = CFE_PSP_SUCCESS;
                    state->is_running = true;
                }
            }
        }
    }

    return StatusCode;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * linux_sysmon_Stop()
 * ------------------------------------------------------
 *  Stops the cpu load watcher function
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int32_t linux_sysmon_Stop(linux_sysmon_statinfo_state_t *state)
{
    if (state->is_running)
    {
        state->should_run = false;
        state->is_running = false;
        pthread_cancel(state->task_id);
        pthread_join(state->task_id, NULL);
        close(state->stat_fd);
    }

    return CFE_PSP_SUCCESS;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * linux_sysmon_aggregate_dispatch()
 * ------------------------------------------------------
 *  Handle a request on the aggregate subsystem (main)
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int32_t linux_sysmon_aggregate_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t                        StatusCode;
    linux_sysmon_statinfo_state_t *state;

    /* There is just one global cpuload object */
    state      = &linux_sysmon_global.statinfo;
    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (CommandCode)
    {
        case CFE_PSP_IODriver_NOOP:
        case CFE_PSP_IODriver_ANALOG_IO_NOOP:
        {
            /* NO-OP should return success -
             * This is a required opcode as "generic" clients may use it to
             * determine if a certain set of opcodes are supported or not
             */
            StatusCode = CFE_PSP_SUCCESS;
            break;
        }
        /* Start/stop opcodes */
        case CFE_PSP_IODriver_SET_RUNNING: /**< int32_t argument, 0=stop 1=start device */
        {
            if (Arg.U32)
            {
                StatusCode = linux_sysmon_Start(state);
            }
            else
            {
                StatusCode = linux_sysmon_Stop(state);
            }
            break;
        }
        case CFE_PSP_IODriver_GET_RUNNING: /**< no argument, returns positive nonzero (true) if running and zero (false)
                                              if stopped, negative on error */
        {
            StatusCode = state->is_running;
            break;
        }
        case CFE_PSP_IODriver_SET_CONFIGURATION: /**< const string argument (device-dependent content) */
        case CFE_PSP_IODriver_GET_CONFIGURATION: /**< void * argument (device-dependent content) */
        {
            /* not implemented for now */
            break;
        }
        case CFE_PSP_IODriver_LOOKUP_SUBSYSTEM: /**< const char * argument, looks up name and returns positive
                                                    value for subsystem number, negative value for error */
        {
            uint16_t i;

            for (i = 0; i < LINUX_SYSMON_MAX_SUBSYS; ++i)
            {
                if (strcmp(Arg.ConstStr, linux_sysmon_subsystem_names[i]) == 0)
                {
                    StatusCode = i;
                    break;
                }
            }

            break;
        }
        case CFE_PSP_IODriver_LOOKUP_SUBCHANNEL: /**< const char * argument, looks up name and returns positive
                                                    value for channel number, negative value for error */
        {
            uint16_t i;

            for (i = 0; i < LINUX_SYSMON_AGGR_MAX_SUBCH; ++i)
            {
                if (strcmp(Arg.ConstStr, linux_sysmon_aggregate_subchannel_names[i]) == 0)
                {
                    StatusCode = i;
                    break;
                }
            }

            break;
        }
        case CFE_PSP_IODriver_QUERY_DIRECTION: /**< CFE_PSP_IODriver_Direction_t argument */
        {
            CFE_PSP_IODriver_Direction_t *DirPtr = (CFE_PSP_IODriver_Direction_t *)Arg.Vptr;
            if (DirPtr != NULL)
            {
                *DirPtr    = CFE_PSP_IODriver_Direction_INPUT_ONLY;
                StatusCode = CFE_PSP_SUCCESS;
            }
            break;
        }
        case CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS:
        {
            CFE_PSP_IODriver_AnalogRdWr_t *RdWr = Arg.Vptr;

            if (RdWr->NumChannels == 1 && Subchannel == LINUX_SYSMON_AGGR_CPULOAD_SUBCH)
            {
                *RdWr->Samples = linux_sysmon_get_aggregate_load(state);
                StatusCode     = CFE_PSP_SUCCESS;
            }
            break;
        }
        default:
            break;
    }

    return StatusCode;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * linux_sysmon_cpu_load_dispatch()
 * ------------------------------------------------------
 *  Handle a request on any of the per-cpu subsystems
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int32_t linux_sysmon_cpu_load_dispatch(uint32_t               CommandCode,
                                       uint16_t               Subchannel,
                                       CFE_PSP_IODriver_Arg_t Arg,
                                       CFE_PSP_IODriver_AdcCode_t (*load_reader)(linux_sysmon_statinfo_state_t *state,
                                                                                 uint32_t core_num))
{
    int32_t                        StatusCode;
    linux_sysmon_statinfo_state_t *state;

    /* There is just one global cpuload object */
    state      = &linux_sysmon_global.statinfo;
    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (CommandCode)
    {
        case CFE_PSP_IODriver_NOOP:
        case CFE_PSP_IODriver_ANALOG_IO_NOOP:
        {
            /* NO-OP should return success -
             * This is a required opcode as "generic" clients may use it to
             * determine if a certain set of opcodes are supported or not
             */
            StatusCode = CFE_PSP_SUCCESS;
            break;
        }
        case CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS:
        {
            CFE_PSP_IODriver_AnalogRdWr_t *RdWr = Arg.Vptr;
            uint32_t                       ch;

            if (Subchannel < state->num_cpus && (Subchannel + RdWr->NumChannels) <= state->num_cpus)
            {
                for (ch = 0; ch < RdWr->NumChannels; ++ch)
                {
                    RdWr->Samples[ch] = load_reader(state, ch + Subchannel);
                }
            }
            break;
        }
        default:
            break;
    }

    return StatusCode;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*    linux_sysmon_DevCmd()                                         */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * \brief Main entry point for API.
 *
 * This function is called through iodriver to invoke the linux_sysmon module.
 *
 * \par Assumptions, External Events, and Notes:
 *          None
 *
 * \param[in] CommandCode  The CFE_PSP_IODriver_xxx command.
 * \param[in] SubsystemId  The monitor subsystem identifier
 * \param[in] SubchannelId The monitor subchannel identifier
 * \param[in] Arg          The arguments for the corresponding command.
 *
 * \returns Status code
 * \retval #CFE_PSP_SUCCESS if successful
 */
int32_t
linux_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t StatusCode;

    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (SubsystemId)
    {
        case LINUX_SYSMON_AGGREGATE_SUBSYS:
            StatusCode = linux_sysmon_aggregate_dispatch(CommandCode, SubchannelId, Arg);
            break;
        case LINUX_SYSMON_CPULOAD_SUBSYS:
            StatusCode = linux_sysmon_cpu_load_dispatch(CommandCode,
                                                        SubchannelId,
                                                        Arg,
                                                        linux_sysmon_get_single_core_nonidle_load);
            break;
        case LINUX_SYSMON_PERCPU_USER_SUBSYS:
            StatusCode =
                linux_sysmon_cpu_load_dispatch(CommandCode, SubchannelId, Arg, linux_sysmon_get_single_core_user_load);
            break;
        case LINUX_SYSMON_PERCPU_KERNEL_SUBSYS:
            StatusCode = linux_sysmon_cpu_load_dispatch(CommandCode,
                                                        SubchannelId,
                                                        Arg,
                                                        linux_sysmon_get_single_core_system_load);
            break;
        default:
            /* not implemented */
            break;
    }

    return StatusCode;
}
