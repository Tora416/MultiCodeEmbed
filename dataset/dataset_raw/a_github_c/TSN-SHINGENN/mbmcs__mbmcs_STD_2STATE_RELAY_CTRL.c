




#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "mbmcs_stdio.h"
#include "mbmcs_STD_2STATE_RELAY_CTRL.h"


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



#define RELAY_OP_STAT_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x0))
#define RELAY_DELAY_PERIOD_THRESH_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x8))
#define RELAY_ACTIVE_PERIOD_THRESH_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0xC))
#define RELAY_DELAY_TIMERCNT_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x10))
#define RELAY_ACTIVE_TIMERCNT_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x14))
#define RELAY_TEST_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x1C))

#define MBMCS_EXTTEND_MODULE_MEMMAP_ADDR 0xC0000000
#define MBMCS_MEMALIGN 4

#define RELAY_MODULE_CTL_ENABLE_BIT   ((uint32_t)0x1)
#define RELAY_MODULE_CTL_ENABLE_SHIFT (31)
#define RELAY_MODULE_CTL_ENABLE_MASK \
    (RELAY_MODULE_CTL_ENABLE_BIT << RELAY_MODULE_CTL_ENABLE_SHIFT)

#define RELAY_MODULE_CTL_ENABLE_INTR_BIT   ((uint32_t)0x1)
#define RELAY_MODULE_CTL_ENABLE_INTR_SHIFT (30)
#define RELAY_MODULE_CTL_ENABLE_INTR_MASK \
    (RELAY_MODULE_CTL_ENABLE_INTR_BIT << RELAY_MODULE_CTL_ENABLE_INTR_SHIFT)

#define RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_BIT ((uint32_t)0x1)
#define RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_SHIFT (28)
#define RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_MASK \
    (RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_BIT << RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_SHIFT)


#define RELAY_MODULE_STAT_DELAY_THRESHED_INTERRUPT_BIT  ((uint32_t)0x1)
#define RELAY_MODULE_STAT_DELAY_THRESHED_INTERRUPT_SHIFT  (7)
#define RELAY_MODULE_STAT_DELAY_THRESHED_INTERRUPT_MASK  \
    (RELAY_MODULE_STAT_DELAY_THRESHED_INTERRUPT_BIT << RELAY_MODULE_STAT_DELAY_THRESHED_INTERRUPT_SHIFT)

#define RELAY_MODULE_STAT_ACTIVE_THRESHED_INTERRUPT_BIT  ((uint32_t)0x1)
#define RELAY_MODULE_STAT_ACTIVE_THRESHED_INTERRUPT_SHIFT  (6)
#define RELAY_MODULE_STAT_ACTIVE_THRESHED_INTERRUPT_MASK  \
    (RELAY_MODULE_STAT_ACTIVE_THRESHED_INTERRUPT_BIT << RELAY_MODULE_STAT_ACTIVE_THRESHED_INTERRUPT_SHIFT)

#define RELAY_MODULE_STAT_DELAY_TIMER_IS_ACTIVE_BIT  ((uint32_t)0x1)
#define RELAY_MODULE_STAT_DELAY_TIMER_IS_ACTIVE_SHIFT (5)
#define RELAY_MODULE_STAT_DELAY_TIMER_IS_ACTIVE_MASK \
    (RELAY_MODULE_STAT_DELAY_TIMER_IS_ACTIVE_BIT << RELAY_MODULE_STAT_DELAY_TIMER_IS_ACTIVE_SHIFT)

#define RELAY_MODULE_STAT_ACTIVE_TIMER_IS_ACTIVE_BIT  ((uint32_t)0x1)
#define RELAY_MODULE_STAT_ACTIVE_TIMER_IS_ACTIVE_SHIFT (4)
#define RELAY_MODULE_STAT_ACTIVE_TIMER_IS_ACTIVE_MASK \
    (RELAY_MODULE_STAT_ACTIVE_TIMER_IS_ACTIVE_BIT << RELAY_MODULE_STAT_ACTIVE_TIMER_IS_ACTIVE_SHIFT)


#define RELAY_MODULE_CTL_EXEC_CLEAR_BIT ((uint32_t)0x1)
#define RELAY_MODULE_CTL_EXEC_CLEAR_SHIFT (3)
#define RELAY_MODULE_CTL_EXEC_CLEAR_MASK \
    (RELAY_MODULE_CTL_EXEC_CLEAR_BIT << RELAY_MODULE_CTL_EXEC_CLEAR_SHIFT)

#define RELAY_MODULE_CTL_EXEC_PAUSE_BIT ((uint32_t)0x1)
#define RELAY_MODULE_CTL_EXEC_PAUSE_SHIFT (2)
#define RELAY_MODULE_CTL_EXEC_PAUSE_MASK \
    (RELAY_MODULE_CTL_EXEC_PAUSE_BIT << RELAY_MODULE_CTL_EXEC_PAUSE_SHIFT)

#define RELAY_MODULE_CTL_EXEC_CONTINUE_BIT ((uint32_t)0x1)
#define RELAY_MODULE_CTL_EXEC_CONTINUE_SHIFT (1)
#define RELAY_MODULE_CTL_EXEC_CONTINUE_MASK \
    (RELAY_MODULE_CTL_EXEC_CONTINUE_BIT << RELAY_MODULE_CTL_EXEC_CONTINUE_SHIFT)

#define RELAY_MODULE_CTL_EXEC_START_BIT ((uint32_t)0x1)
#define RELAY_MODULE_CTL_EXEC_START_SHIFT (0)
#define RELAY_MODULE_CTL_EXEC_START_MASK \
    (RELAY_MODULE_CTL_EXEC_START_BIT << RELAY_MODULE_CTL_EXEC_START_SHIFT)

#define RELAY_MODULE_STAT_BUSY_BIT ((uint32_t)0x1)
#define RELAY_MODULE_STAT_BUSY_SHIFT (29)
#define RELAY_MODULE_STAT_BUSY_MASK \
    (RELAY_MODULE_STAT_BUSY_BIT << RELAY_MODULE_STAT_BUSY_SHIFT)



extern int mbmcs_std_2state_relay_ctrl_init(mbmcs_std_2state_relay_ctrl_t * const self_p, const uintptr_t base_addr)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_relay_ctrl_irq_enable(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));

extern int mbmcs_std_2state_relay_ctrl_delay_timer_is_active(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));

extern void mbmcs_std_2state_relay_ctrl_exec_pause(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_relay_ctrl_exec_clear(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_relay_ctrl_exec_continue(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_relay_ctrl_exec_start(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));

extern int mbmcs_std_2state_relay_ctrl_is_busy(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));

extern int mbmcs_std_2state_relay_ctrl_ative_timer_is_active(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));
extern int mbmcs_std_2state_relay_ctrl_delay_timer_is_active(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));

extern void mbmcs_std_2state_relay_ctrl_set_pause_at_active_thresh(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern int mbmcs_std_2state_relay_ctrl_get_flag_pause_at_active_thresh(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));

extern uint32_t mbmcs_std_2state_relay_ctrl_get_delay_timer_counter(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));
extern uint32_t mbmcs_std_2state_relay_ctrl_get_active_timer_counter(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));

extern int mbmcs_std_2state_relay_ctrl_set_delay_timer_thresh_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint32_t msec)
    __attribute__ ((optimize("O2")));

extern int mbmcs_std_2state_relay_ctrl_set_active_timer_thresh_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint32_t msec)
    __attribute__ ((optimize("O2")));

extern uint32_t mbmcs_std_2state_get_delay_timer_count_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));
extern uint32_t mbmcs_std_2state_relay_ctrl_relay_ctrl_get_active_timer_count_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p)
    __attribute__ ((optimize("O2")));

extern void mbmcs_std_2state_relay_get_interrupt_flags(const mbmcs_std_2state_relay_ctrl_t * const self_p, mbmcs_std_2state_relay_ctrl_interrupt_status_t * const intr_stat_p)
    __attribute__ ((optimize("O2")));



int mbmcs_std_2state_relay_ctrl_init(mbmcs_std_2state_relay_ctrl_t * const self_p, const uintptr_t base_addr)
{

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    if((base_addr < MBMCS_EXTTEND_MODULE_MEMMAP_ADDR) ||  ( base_addr % MBMCS_MEMALIGN )) {
    return EINVAL;
    }

    self_p->base_addr = base_addr;

    {
        uint32_t reg32 = RELAY_MODULE_CTL_ENABLE_MASK;
        RELAY_OP_STAT_REG(self_p->base_addr) = reg32;
    }

    for(;;) {
        uint32_t reg32;
    reg32 = RELAY_OP_STAT_REG(self_p->base_addr);
    if(!(reg32 & RELAY_MODULE_STAT_BUSY_MASK)) {
        return 0;
        }
    }
    return EPERM;
}

void mbmcs_std_2state_relay_ctrl_irq_enable(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint8_t is_on)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    if(is_on) {
    reg32 |= RELAY_MODULE_CTL_ENABLE_INTR_MASK;
    } else {
    reg32 &= ~RELAY_MODULE_CTL_ENABLE_INTR_MASK;
    }
    RELAY_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_std_2state_relay_ctrl_set_pause_at_active_thresh(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint8_t is_on)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    if(is_on) {
    reg32 |= RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_MASK;
    } else {
    reg32 &= ~RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_MASK;
    }
    RELAY_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

int mbmcs_std_2state_relay_ctrl_get_flag_pause_at_active_thresh(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    const uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    return (reg32 & RELAY_MODULE_CTL_PAUSE_AT_ACTIVE_THRESHED_MASK) ? (~0) : 0;

}

void mbmcs_std_2state_relay_ctrl_exec_pause(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    reg32 |= RELAY_MODULE_CTL_EXEC_PAUSE_MASK;

    RELAY_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_std_2state_relay_ctrl_exec_clear(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    reg32 |= RELAY_MODULE_CTL_EXEC_CLEAR_MASK;

    RELAY_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_std_2state_relay_ctrl_exec_continue(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    reg32 |= RELAY_MODULE_CTL_EXEC_CONTINUE_MASK;

    RELAY_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_std_2state_relay_ctrl_exec_start(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    reg32 |= RELAY_MODULE_CTL_EXEC_START_MASK;

    RELAY_OP_STAT_REG(self_p->base_addr) = reg32;
}

int mbmcs_std_2state_relay_ctrl_is_busy(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    reg32 &= RELAY_MODULE_STAT_BUSY_MASK;

    return (reg32) ? ~0 : 0;
}

int mbmcs_std_2state_relay_ctrl_ative_timer_is_active(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);
    
    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    reg32 &= RELAY_MODULE_STAT_ACTIVE_TIMER_IS_ACTIVE_BIT;

    return (reg32) ? ~0 : 0;
}

int mbmcs_std_2state_relay_ctrl_delay_timer_is_active(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    reg32 &= RELAY_MODULE_STAT_DELAY_TIMER_IS_ACTIVE_BIT;

    return (reg32) ? ~0 : 0;
}

int mbmcs_std_2state_relay_ctrl_set_delay_timer_thresh_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint32_t msec)
{
    const uint32_t reg32 = (msec * 10);
    uint32_t tmp32;

    DBMS3(stderr, "%s : execte addr=0x%08x reg32=0x%08x" EOL_CRLF, __FUNCTION__,
            self_p->base_addr, reg32);

    RELAY_DELAY_PERIOD_THRESH_REG(self_p->base_addr) = reg32;

    tmp32=RELAY_DELAY_PERIOD_THRESH_REG(self_p->base_addr);

    DBMS3(stderr, "%s : addr=0x%08x tmp32=0x%08x" EOL_CRLF, __FUNCTION__,
            self_p->base_addr, tmp32);
 
    return !(reg32 - tmp32) ? 0 : EOVERFLOW;
}

int mbmcs_std_2state_relay_ctrl_set_active_timer_thresh_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p, const uint32_t msec)
{
    uint32_t reg32 = (msec * 10), tmp32;

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    RELAY_ACTIVE_PERIOD_THRESH_REG(self_p->base_addr) = reg32;

    tmp32=RELAY_ACTIVE_PERIOD_THRESH_REG(self_p->base_addr);
 
    return !(reg32 - tmp32) ? 0 : EOVERFLOW;
}

uint32_t mbmcs_std_2state_relay_ctrl_get_delay_timer_count_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    const uint32_t reg32 = RELAY_DELAY_TIMERCNT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    return (reg32 / 10);
}

uint32_t mbmcs_std_2state_relay_ctrl_get_active_timer_count_msec(const mbmcs_std_2state_relay_ctrl_t * const self_p)
{
    const uint32_t reg32 = RELAY_ACTIVE_TIMERCNT_REG(self_p->base_addr);

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    return (reg32 / 10);
}

void mbmcs_std_2state_relay_get_interrupt_flags(const mbmcs_std_2state_relay_ctrl_t * const self_p, mbmcs_std_2state_relay_ctrl_interrupt_status_t * const intr_stat_p)
{
    uint32_t reg32 = RELAY_OP_STAT_REG(self_p->base_addr);
    mbmcs_std_2state_relay_ctrl_interrupt_status_t intr_stat;

    DBMS5(stderr, "%s : execte" EOL_CRLF, __FUNCTION__);

    intr_stat.flags = 0;
    if(reg32 & RELAY_MODULE_STAT_DELAY_THRESHED_INTERRUPT_MASK) {
        intr_stat.f.is_delay_threshed = 1;
    }

    if(reg32 & RELAY_MODULE_STAT_ACTIVE_THRESHED_INTERRUPT_MASK) {
        intr_stat.f.is_active_threshed = 1;
    }

    reg32 &= ~(RELAY_MODULE_STAT_DELAY_THRESHED_INTERRUPT_MASK |
    RELAY_MODULE_STAT_ACTIVE_THRESHED_INTERRUPT_MASK);

    RELAY_OP_STAT_REG(self_p->base_addr) = reg32;

    *intr_stat_p = intr_stat;

    return;
}
