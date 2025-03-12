/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/* PSP coverage stub replacement for stdlib.h */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utstubs.h"
#include "utassert.h"

#include "PCS_stdlib.h"

/*
 * The malloc emulator relies on two magic numbers;
 * one at the start of the pool, one for each block allocated.
 *
 * Note that the malloc emulator is not a real allocator,
 * it only allocates sequential blocks and does not recover
 * the space after free.
 */
#define MPOOL_START_SIGNATURE 0x8a458c6b
#define MPOOL_BLOCK_SIGNATURE 0x3ef65721
#define MPOOL_ALIGN           16

struct MPOOL_REC
{
    cpuaddr BlockAddr;
    uint32  Magic;
    uint32  Size;
};

void UT_DefaultHandler_PCS_strtoul(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* unsigned long int PCS_strtoul(const char *nptr, char **endptr, int base) */
    const char *nptr   = UT_Hook_GetArgValueByName(Context, "nptr", const char *);
    char **     endptr = UT_Hook_GetArgValueByName(Context, "endptr", char **);
    int         base   = UT_Hook_GetArgValueByName(Context, "base", int);

    unsigned long Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* do the real op */
        Result = strtoul(nptr, endptr, base);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_malloc(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void *PCS_malloc(size_t sz) */
    size_t sz = UT_Hook_GetArgValueByName(Context, "sz", size_t);

    int32             Status;
    void *            PoolPtr;
    cpuaddr           PoolStart;
    cpuaddr           PoolEnd;
    cpuaddr           NextBlock;
    size_t            NextSize;
    size_t            PoolSize;
    uint32            CallCnt;
    void *            BlockPtr;
    struct MPOOL_REC *Rec;

    Rec      = NULL;
    BlockPtr = NULL;
    CallCnt  = UT_GetStubCount(UT_KEY(PCS_malloc));
    UT_GetDataBuffer(UT_KEY(PCS_malloc), &PoolPtr, &PoolSize, NULL);

    if (PoolPtr != NULL)
    {
        PoolStart = (cpuaddr)PoolPtr;
        PoolEnd   = PoolStart + PoolSize;
        PoolStart = (PoolStart + MPOOL_ALIGN - 1) & ~((cpuaddr)MPOOL_ALIGN - 1);
        PoolSize  = PoolEnd - PoolStart;

        /*
         * Verify PollSize is greater than minimun size and
         * that PoolStart didn't go past the PoolEnd during alignment.
         */
        if (PoolSize > (MPOOL_ALIGN * 2) && PoolStart < PoolEnd)
        {
            Rec       = (struct MPOOL_REC *)PoolStart;
            NextBlock = PoolStart + MPOOL_ALIGN;
            PoolSize -= MPOOL_ALIGN;
            if (CallCnt == 1)
            {
                Rec->Magic     = MPOOL_START_SIGNATURE;
                Rec->Size      = 0;
                Rec->BlockAddr = NextBlock;
            }
            else if (Rec->Magic != MPOOL_START_SIGNATURE)
            {
                UtAssert_Failed("PCS_malloc() heap corruption detected");
            }
        }
    }

    UT_Stub_GetInt32StatusCode(Context, &Status);

    if (Status == 0 && Rec != NULL)
    {
        NextSize = Rec->Size + sz + MPOOL_ALIGN;
        if (NextSize > PoolSize)
        {
            /*
             * This indicates that the application is trying to allocate
             * a block larger than the pool.  It typically means that the
             * emulated heap size is too small, so it is prudent to generate
             * a message.
             */
            UtAssert_Failed("PCS_malloc() heap has been exhausted");
        }
        else
        {
            NextSize  = (NextSize + MPOOL_ALIGN - 1) & ~((size_t)MPOOL_ALIGN - 1);
            NextBlock = Rec->BlockAddr + MPOOL_ALIGN;
            Rec->BlockAddr += NextSize;
            Rec->Size += NextSize;

            Rec            = (struct MPOOL_REC *)(NextBlock - sizeof(struct MPOOL_REC));
            Rec->BlockAddr = NextBlock;
            Rec->Magic     = MPOOL_BLOCK_SIGNATURE;
            Rec->Size      = sz;

            BlockPtr = (void *)NextBlock;
        }

        UT_Stub_SetReturnValue(FuncKey, BlockPtr);
    }
}

void UT_DefaultHandler_PCS_free(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void PCS_free(void *ptr) */
    void *ptr = UT_Hook_GetArgValueByName(Context, "ptr", void *);

    int32             Status;
    cpuaddr           BlockAddr;
    void *            PoolPtr;
    size_t            PoolSize;
    struct MPOOL_REC *Rec;

    /*
     * If there is a data buffer associated with free() then this
     * will sanity-check that the block being freed came from that heap.
     */
    PoolPtr  = NULL;
    PoolSize = 0;
    UT_GetDataBuffer(UT_KEY(PCS_free), &PoolPtr, &PoolSize, NULL);

    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status == 0 && PoolPtr != NULL)
    {
        BlockAddr = (cpuaddr)ptr;
        if (BlockAddr < (cpuaddr)PoolPtr || BlockAddr >= ((cpuaddr)PoolPtr + PoolSize))
        {
            UtAssert_Failed("PCS_free(): Heap corruption -- Non-Heap pointer");
        }
        else
        {
            Rec = (struct MPOOL_REC *)(BlockAddr - sizeof(struct MPOOL_REC));
            if (Rec->Magic == MPOOL_BLOCK_SIGNATURE)
            {
                Rec->Magic = ~MPOOL_BLOCK_SIGNATURE;
            }
            else if (Rec->Magic == ~MPOOL_BLOCK_SIGNATURE)
            {
                UtAssert_Failed("PCS_free(): Heap corruption -- Double free detected");
            }
            else
            {
                UtAssert_Failed("PCS_free(): Heap corruption -- Corrupted block detected");
            }
        }
    }
}
