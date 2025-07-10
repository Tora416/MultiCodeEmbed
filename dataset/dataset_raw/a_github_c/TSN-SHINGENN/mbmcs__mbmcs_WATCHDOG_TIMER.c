




#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "mbmcs_stdio.h"
#include "mbmcs_WATCHDOG_TIMER.h"



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



#define WDT_OP_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x0))
#define WDT_OUNTER_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x4))

#define MBMCS_EXTTEND_MODULE_MEMMAP_ADDR 0xC0000000
#define MBMCS_MEMALIGN 4


#define WDT_MODULE_ENABLE_BIT ((uint32_t)0x1)
#define WDT_MODULE_ENABLE_SHIFT (31)
#define WDT_MODULE_ENABLE_MASK \
    ( WDT_MODULE_ENABLE_BIT << WDT_MODULE_ENABLE_SHIFT)
#define WDT_IRQ_ENABLE_BIT ((uint32_t)0x1)
#define WDT_IRQ_ENABLE_SHIFT (30)
#define WDT_IRQ_ENABLE_MASK \
    ( WDT_IRQ_ENABLE_BIT << WDT_IRQ_ENABLE_SHIFT)
#define WDT_TIMEDOUT_BIT ((uint32_t)0x1)
#define WDT_TIMEDOUT_SHIFT (29)
#define WDT_TIMEDOUT_MASK \
    ( WDT_TIMEDOUT_BIT << WDT_TIMEDOUT_SHIFT)
#define WDT_TIMER_THRESHED_BIT   ((uint32_t)0xffff)
#define WDT_TIMER_THRESHED_SHIFT (0)
#define WDT_TIMER_THRESHED_MASK \
    ( WDT_TIMER_THRESHED_BIT << WDT_TIMER_THRESHED_SHIFT)
#define WDT_IRQ_TIMER_THRESH_BIT ((uint32_t)0xfff)
#define WDT_IRQ_TIMER_THRESH_SHIFT (16)
#define WDT_IRQ_TIMER_THRESH_MASK \
    ( WDT_IRQ_TIMER_THRESH_BIT << WDT_IRQ_TIMER_THRESH_SHIFT)
#define WDT_IRQ_TIMER_LSB_MASK ((uint32_t)0xf)
#define WDT_IRQ_TIMER_LSB_SHIFT (4)



extern int mbmcs_watchdog_timer_init(mbmcs_watchdog_timer_t *const, uintptr_t)
    __attribute__ ((optimize("Os")));
extern void mbmcs_watchdog_timer_set_thresh(mbmcs_watchdog_timer_t const *const, const uint16_t)
    __attribute__ ((optimize("O2")));
extern void mbmcs_watchdog_timer_set_irq_thresh(mbmcs_watchdog_timer_t const *const, uint16_t)
    __attribute__ ((optimize("O2")));
extern void mbmcs_watchdog_timer_enable(mbmcs_watchdog_timer_t const *const,bool)
    __attribute__ ((optimize("O2")));
extern void mbmcs_watchdog_timer_irq_enable(mbmcs_watchdog_timer_t const *const, bool)
    __attribute__ ((optimize("O2")));
extern void mbmcs_watchdog_timer_interval_reset(mbmcs_watchdog_timer_t const *const)
    __attribute__ ((optimize("O2")));
extern void _mbmcs_watchdog_timer_dump_ctrl_reg(mbmcs_watchdog_timer_t const *const)
    __attribute__ ((optimize("O2")));

int mbmcs_watchdog_timer_init(mbmcs_watchdog_timer_t *const self_p, uintptr_t base_addr)
{
    DBMS5(stderr, "%s : execute" EOL_CRLF, __FUNCTION__);

    if((base_addr < MBMCS_EXTTEND_MODULE_MEMMAP_ADDR) ||  ( base_addr % MBMCS_MEMALIGN )) {
    return EINVAL;
    }

    self_p->base_addr = base_addr;

    
    WDT_OP_REG(self_p->base_addr) = 0x0;

    
    while(WDT_TIMEDOUT_MASK & WDT_OP_REG(self_p->base_addr));

    return 0;
}

void mbmcs_watchdog_timer_set_thresh(mbmcs_watchdog_timer_t const *const self_p, const uint16_t thresh)
{
    uint32_t reg32 = WDT_OP_REG(self_p->base_addr);

    reg32 &= ~WDT_TIMER_THRESHED_MASK;
    reg32 |= (WDT_TIMER_THRESHED_BIT & thresh);

    WDT_OP_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_watchdog_timer_set_irq_thresh(mbmcs_watchdog_timer_t const *const self_p, uint16_t thresh)
{
    uint32_t reg32 = WDT_OP_REG(self_p->base_addr);
    const uint32_t irq_thresh =  (WDT_IRQ_TIMER_THRESH_BIT & ((uint32_t)thresh >> WDT_IRQ_TIMER_LSB_SHIFT));

    reg32 &= ~WDT_IRQ_TIMER_THRESH_MASK;
    reg32 |= (irq_thresh << WDT_IRQ_TIMER_THRESH_SHIFT);

    WDT_OP_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_watchdog_timer_enable(mbmcs_watchdog_timer_t const *const self_p, const bool is_true)
{
    uint32_t reg32 = WDT_OP_REG(self_p->base_addr);

    reg32 &= ~WDT_MODULE_ENABLE_MASK;
    if(is_true==true) {
    reg32 |= WDT_MODULE_ENABLE_MASK;
    }

    WDT_OP_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_watchdog_timer_irq_enable(mbmcs_watchdog_timer_t const *const self_p, const bool is_true)
{
    uint32_t reg32 = WDT_OP_REG(self_p->base_addr);

    reg32 &= ~WDT_IRQ_ENABLE_MASK;
    if(is_true==true) {
    reg32 |= WDT_IRQ_ENABLE_MASK;
    } 
    WDT_OP_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_watchdog_timer_interval_reset(mbmcs_watchdog_timer_t const *const self_p)
{
    WDT_OUNTER_REG(self_p->base_addr) = 0;

    return;
}

void _mbmcs_watchdog_timer_dump_ctrl_reg(mbmcs_watchdog_timer_t const *const self_p)
{
    uint32_t reg32 = WDT_OP_REG(self_p->base_addr);

    xil_printf("watchdog 0x%08x : 0x%08x" EOL_CRLF, self_p->base_addr, reg32);
}
