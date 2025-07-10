


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>


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


#include "mbmcs_LIMITED_MOTION_2STATE_SWITCH.h"

#define MBMCS_EXTTEND_MODULE_MEMMAP_ADDR 0xC0000000
#define MBMCS_MEMALIGN 4

#define LMSW_OP_STAT_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x0))
#define LMSW_THRESHOLD_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x4))

#define LMSW_MODULE_OP_ENABLE_BIT ((uint32_t)0x1)
#define LMSW_MODULE_OP_ENABLE_SHIFT (31)
#define LMSW_MODULE_OP_ENABLE_MASK \
    (LMSW_MODULE_OP_ENABLE_BIT << LMSW_MODULE_OP_ENABLE_SHIFT)
#define LMSW_OP_INTR_ENABLE_BIT ((uint32_t)0x1)
#define LMSW_OP_INTR_ENABLE_SHIFT (30)
#define LMSW_OP_INTR_ENABLE_MASK \
    (LMSW_OP_INTR_ENABLE_BIT << LMSW_OP_INTR_ENABLE_SHIFT)
#define LMSW_OP_INITIALIZED_BIT ((uint32_t)0x1)
#define LMSW_OP_INITIALIZED_SHIFT (27)
#define LMSW_ST_INITIALIZED_MASK \
    (LMSW_OP_INITIALIZED_BIT << LMSW_OP_INITIALIZED_SHIFT)

#define LMSW_ST_CURRENT_LEVEL_BIT ((uint32_t)0x1)
#define LMSW_ST_CURRENT_LEVEL_SHIFT (2)
#define LMSW_ST_CURRENT_LEVEL_MASK \
    (LMSW_ST_CURRENT_LEVEL_BIT << LMSW_ST_CURRENT_LEVEL_SHIFT)

#define LMSW_ST_TIMEDOUT_BIT ((uint32_t)0x1)
#define LMSW_ST_TIMEDOUT_SHIFT (1)
#define LMSE_ST_TIMEDOUT_MASK \
    (LMSW_ST_TIMEDOUT_BIT << LMSW_ST_TIMEDOUT_SHIFT)

#define LMSW_ST_INTIME_BIT ((uint32_t)0x1)
#define LMSW_ST_INTIME_SHIFT (0)
#define LMSW_ST_INTIME_MASK \
    (LMSW_ST_INTIME_BIT << LMSW_ST_INTIME_SHIFT)


extern int mbmcs_limited_motion_2state_switch_init( mbmcs_limited_motion_2state_switch_t * const, const uintptr_t )
    __attribute__ ((optimize("O2")));

extern void mbmcs_limited_motion_2state_switch_irq_enable(const mbmcs_limited_motion_2state_switch_t *, bool)
    __attribute__ ((optimize("O2")));

void mbmcs_limited_motion_2state_switch_get_interrupt_status(const mbmcs_limited_motion_2state_switch_t *const, mbmcs_limited_motion_2state_switch_status_t *)
    __attribute__ ((optimize("O2")));

extern void mbmcs_limited_motion_2state_switch_clear_interrupt_status(const mbmcs_limited_motion_2state_switch_t *const)
    __attribute__ ((optimize("O2")));

extern void mbmcs_limited_motion_2state_switch_set_limited_timer(const mbmcs_limited_motion_2state_switch_t *const, const uint16_t)
    __attribute__ ((optimize("O2")));


int mbmcs_limited_motion_2state_switch_init( mbmcs_limited_motion_2state_switch_t * const self_p, const uintptr_t base_addr)
{
    if((base_addr < MBMCS_EXTTEND_MODULE_MEMMAP_ADDR) ||  ( base_addr % MBMCS_MEMALIGN )) {
    return EINVAL;
    }

    self_p->base_addr = base_addr;
    LMSW_OP_STAT_REG(self_p->base_addr) = (uint32_t)LMSW_MODULE_OP_ENABLE_MASK;

    for(;;) {
    uint32_t reg32;
    reg32 = LMSW_OP_STAT_REG(self_p->base_addr);
    if( reg32 & LMSW_ST_INITIALIZED_MASK) {
        return 0;
    }
    }
    return EPERM;
}

void mbmcs_limited_motion_2state_switch_get_interrupt_status(const mbmcs_limited_motion_2state_switch_t *const self_p, mbmcs_limited_motion_2state_switch_status_t *const stat_p)
{
    const uint32_t reg32 = LMSW_OP_STAT_REG(self_p->base_addr);
    mbmcs_limited_motion_2state_switch_status_t stat;

    stat.flags = 0;

    if(reg32 & LMSW_ST_CURRENT_LEVEL_MASK) {
    stat.f.cur_level = 0x1;
    }

    if(reg32 & LMSE_ST_TIMEDOUT_MASK) {
    stat.f.timedout = 0x1;
    }

    if(reg32 & LMSW_ST_INTIME_MASK ) {
    stat.f.intime = 0x1;
    }

    *stat_p = stat;

    return;
}

void mbmcs_limited_motion_2state_switch_clear_interrupt_status(const mbmcs_limited_motion_2state_switch_t *const self_p)
{
    uint32_t reg32 = LMSW_OP_STAT_REG(self_p->base_addr);

    reg32 &= ~(LMSE_ST_TIMEDOUT_MASK | LMSW_ST_INTIME_MASK);

    LMSW_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_limited_motion_2state_switch_set_limited_timer(const mbmcs_limited_motion_2state_switch_t *const self_p, const uint16_t milisec)
{
    const uint32_t reg32 = milisec * 10;

    LMSW_THRESHOLD_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_limited_motion_2state_switch_irq_enable(const mbmcs_limited_motion_2state_switch_t *self_p, bool is_true)
{
    uint32_t reg32 = LMSW_OP_STAT_REG(self_p->base_addr);

    if(is_true== true ) {
    reg32 |= LMSW_OP_INTR_ENABLE_MASK;
    } else {
    reg32 &= ~LMSW_OP_INTR_ENABLE_MASK;
    }

    LMSW_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

