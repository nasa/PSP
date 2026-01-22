/*
 * Checks if this C library provides endian.h.
 * If it does, then this is the preferred method to
 * perform byte ordering conversions, as the implentation
 * is more reliably correct and probably also optimized for
 * the platform, as opposed to checking non-standard compiler
 * defines and making assumptions about it.
 */

#include <stdint.h>
#include <endian.h>

/* make a non-empty unit, invoke one of the functions */
uint16_t test_noop(void)
{
    return htobe16(0x1234);
}
