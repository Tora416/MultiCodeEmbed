




#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "mbmcs_MONOTONIC_TIMER.h"
#include "mbmcs_stdio.h"


#ifdef __GNUC__
__attribute__ ((unused))
#endif
#ifdef DEBUG
static int debuglevel = 4;
#else
static const int debuglevel = 0;
#endif

#include "dbms.h"

#if defined(_MULTIOS_DMSG_IS_UART)
#define EOL_CRLF "\n\r"
#else
#define EOL_CRLF "\n"
#endif



#define MONOTONIC_TIMER_OP_FORCE_CLEAR_PLS_BIT ((uint32_t)0x1)
#define MONOTONIC_TIMER_OP_FORCE_CLEAR_PLS_SHIFT (31)
#define MONOTONIC_TIMER_OP_FORCE_CLEAR_PLS_MASK (MONOTONIC_TIMER_OP_FORCE_CLEAR_PLS_BIT << MONOTONIC_TIMER_OP_FORCE_CLEAR_PLS_SHIFT)

#define MONOTONIC_TIMER_OP_COUNTER_LATCH_MASK_BIT ((uint32_t)0x1)
#define MONOTONIC_TIMER_OP_COUNTER_LATCH_MASK_SHIFT (30)
#define MONOTONIC_TIMER_OP_COUNTER_LATCH_MASK_MASK (MONOTONIC_TIMER_OP_COUNTER_LATCH_MASK_BIT << MONOTONIC_TIMER_OP_COUNTER_LATCH_MASK_BIT)


#define MONOTONIC_TIMER_OP(a) *((volatile unsigned int*)((intptr_t)(a) + 0x0))
#define MONOTONIC_TIMER_LSB(a) *((volatile unsigned int*)((intptr_t)(a) + 0x8))
#define MONOTONIC_TIMER_MSB(a) *((volatile unsigned int*)((intptr_t)(a) + 0xc))


extern void mbmcs_monotonic_timer_init(mbmcs_monotonic_timer_t *const, const uintptr_t)
    __attribute__ ((optimize("Os")));
extern uint64_t mbmcs_monotonic_timer_get_timer_counter( const mbmcs_monotonic_timer_t *const)
    __attribute__ ((optimize("O2")));


void  mbmcs_monotonic_timer_init(mbmcs_monotonic_timer_t *const self_p, const uintptr_t base_addr)
{
    self_p->base_addr = base_addr;

    return;
}

uint64_t mbmcs_monotonic_timer_get_timer_counter( const mbmcs_monotonic_timer_t *const self_p)
{
    volatile uint64_t retval64;
    volatile uint32_t reg32;
    reg32 = MONOTONIC_TIMER_OP(self_p->base_addr);
    reg32 |= MONOTONIC_TIMER_OP_COUNTER_LATCH_MASK_MASK;
    MONOTONIC_TIMER_OP(self_p->base_addr) = reg32;

    retval64 = MONOTONIC_TIMER_MSB(self_p->base_addr);
    
    retval64 <<= 32;
    retval64 |= MONOTONIC_TIMER_LSB(self_p->base_addr);

    reg32 = MONOTONIC_TIMER_OP(self_p->base_addr);
    reg32 &= ~MONOTONIC_TIMER_OP_COUNTER_LATCH_MASK_MASK;
    MONOTONIC_TIMER_OP(self_p->base_addr) = reg32;

    return retval64;
}
