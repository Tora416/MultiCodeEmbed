




#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "mbmcs_stdio.h"
#include "mbmcs_STD_2STATE_SWITCH.h"


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



#define MBMCS_EXTTEND_MODULE_MEMMAP_ADDR 0xC0000000
#define MBMCS_MEMALIGN 4

#define SW_IF_OP_STAT_REG(a) *((volatile uint32_t*)((uintptr_t)(a) + 0x0))
#define SW_IF_MONOTONIC_TIMER64_LSB32_REG(a) *((volatile uint32_t*)((uintptr_t)(a) + 0x8))
#define SW_IF_MONOTONIC_TIMER64_MSB32_REG(a) *((volatile uint32_t*)((uintptr_t)(a) + 0xC))

#define SW_NEGATIVE_EGDE_DETECTIVE_BIT ((uint32_t)0x1)
#define SW_NEGATIVE_EGDE_DETECTIVE_SHIFT  (16)
#define SW_NEGATIVE_EGDE_DETECTIVE_MASK (uint32_t)(SW_NEGATIVE_EGDE_DETECTIVE_BIT << SW_NEGATIVE_EGDE_DETECTIVE_SHIFT)

#define SW_POSITIVE_EGDE_DETECTIVE_BIT ((uint32_t)0x1)
#define SW_POSITIVE_EGDE_DETECTIVE_SHIFT (17)
#define SW_POSITIVE_EDGE_DETECTIVE_MASK (uint32_t)(SW_POSITIVE_EGDE_DETECTIVE_BIT << SW_POSITIVE_EGDE_DETECTIVE_SHIFT)

#define SW_EDGE_DETECTIVE_MASK (uint32_t)(SW_NEGATIVE_EGDE_DETECTIVE_MASK | SW_POSITIVE_EDGE_DETECTIVE_MASK )

#define SW_EDGE_COUNTER_CLEAR_BIT ((uint32_t)0x1)
#define SW_EDGE_COUNTER_CLEAR_SHIFT (25)
#define SW_EDGE_COUNTER_CLEAR_MASK (uint32_t)(SW_EDGE_COUNTER_CLEAR_BIT << SW_EDGE_COUNTER_CLEAR_SHIFT)

#define SW_EDGE_COUNTER_ENABLE_BIT ((uint32_t)0x1)
#define SW_EDGE_COUNTER_ENABLE_SHIFT (24)
#define SW_EDGE_COUNTER_ENABLE_MASK (uint32_t)(SW_EDGE_COUNTER_ENABLE_BIT << SW_EDGE_COUNTER_ENABLE_SHIFT)

#define SW_EDGE_COUNTER_VALUE_BIT ((uint32_t)0xffff)
#define SW_EDGE_COUNTER_VALUE_SHIFT (0)
#define SW_EDGE_COUNTER_VALUE_MASK (uint32_t)(SW_EDGE_COUNTER_VALUE_BIT << SW_EDGE_COUNTER_VALUE_SHIFT)

#define SW_CURRENT_LEVEL_BIT ((uint32_t)0x1)
#define SW_CURRENT_LEVEL_SHIFT (27)
#define SW_CURRENT_LEVEL_MASK (uint32_t)(SW_CURRENT_LEVEL_BIT << SW_CURRENT_LEVEL_SHIFT)

#define SW_INITALIZED_BIT ((uint32_t)0x1)
#define SW_INITALIZED_SHIFT (26)
#define SW_INITALIZED_MASK (uint32_t)(SW_INITALIZED_BIT << SW_INITALIZED_SHIFT)

#define SW_SENS_ENABLE_NEGATIVE_EDGE_BIT ((uint32_t)0x1)
#define SW_SENS_ENABLE_NEGATIVE_EDGE_SHIFT (28)
#define SW_SENS_ENABLE_NEGATIVE_EDGE_MASK (uint32_t)(SW_SENS_ENABLE_NEGATIVE_EDGE_BIT << SW_SENS_ENABLE_NEGATIVE_EDGE_SHIFT)

#define SW_SENS_ENABLE_POSITIVE_EDGE_BIT ((uint32_t)0x1)
#define SW_SENS_ENABLE_POSITIVE_EDGE_SHIFT (29)
#define SW_SENS_ENABLE_POSITIVE_EDGE_MASK (uint32_t)(SW_SENS_ENABLE_POSITIVE_EDGE_BIT << SW_SENS_ENABLE_POSITIVE_EDGE_SHIFT)

#define SW_SENS_ENABLE_EDGE_MASK (uint32_t)(SW_SENS_ENABLE_NEGATIVE_EDGE_MASK | SW_SENS_ENABLE_POSITIVE_EDGE_MASK)

#define SW_IF_IRQ_ENABLE_BIT ((uint32_t)0x1)
#define SW_IF_IRQ_ENABLE_SHIFT (30)
#define SW_IF_IRQ_ENABLE_MASK (uint32_t)(SW_IF_IRQ_ENABLE_BIT << SW_IF_IRQ_ENABLE_SHIFT)

#define SW_IF_MODULE_ENABLE_BIT ((uint32_t)0x1)
#define SW_IF_MODULE_ENABLE_SHIFT (31)
#define SW_IF_MODULE_ENABLE_MASK (uint32_t)(SW_IF_MODULE_ENABLE_BIT << SW_IF_MODULE_ENABLE_SHIFT)

#define SW_IF_MASK (uint32_t)( SW_IF_MODULE_ENABLE_MASK | SW_IF_IRQ_ENABLE_MASK | \
      SW_EDGE_SENS_MASK | SW_EDGE_DETECTIVE_MASK )



extern int mbmcs_std_2state_switch_init(mbmcs_std_2state_switch_t * const self_p, const uintptr_t base_addr)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_switch_sens_negative_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_switch_sens_positive_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_switch_irq_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern int mbmcs_std_2state_switch_get_flags(const mbmcs_std_2state_switch_t * const self_p, mbmcs_std_2state_switch_status_t * const stat_p)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_switch_clear_detective_egde_flags(const mbmcs_std_2state_switch_t * const self_p)
    __attribute__ ((optimize("O2")));
extern uint32_t _mbmcs_std_2state_switch_get_registers(const mbmcs_std_2state_switch_t * const self_p)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_switch_edge_counter_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_true)
    __attribute__ ((optimize("O2")));
extern void mbmcs_std_2state_switch_edge_counter_clear(const mbmcs_std_2state_switch_t * const self_p)
    __attribute__ ((optimize("O2")));
extern uint16_t mbmcs_std_2state_switch_get_edge_counter_value(const mbmcs_std_2state_switch_t * const self_p)
    __attribute__ ((optimize("O2")));
extern uint64_t mbmcs_std_2state_switch_get_monotonic_timer(const mbmcs_std_2state_switch_t * const self_p)
    __attribute__ ((optimize("O2")));




int mbmcs_std_2state_switch_init(mbmcs_std_2state_switch_t * const self_p, const uintptr_t base_addr)
{
    if((base_addr < MBMCS_EXTTEND_MODULE_MEMMAP_ADDR) ||  ( base_addr % MBMCS_MEMALIGN )) {
    return EINVAL;
    }
    self_p->base_addr = base_addr;

    {
        uint32_t reg32 = SW_IF_MODULE_ENABLE_MASK;
        SW_IF_OP_STAT_REG(self_p->base_addr) = reg32;
#define SW_CURRENT_LEVEL_MASK (uint32_t)(SW_CURRENT_LEVEL_BIT << SW_CURRENT_LEVEL_SHIFT)
    }
    for(;;) {
        uint32_t reg32;
    reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);
        if( reg32 & SW_INITALIZED_MASK) {
            mbmcs_std_2state_switch_edge_counter_clear(self_p);
            return 0;
    }
    } 

    return EPERM;
}

 
void mbmcs_std_2state_switch_sens_negative_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_true)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    reg32 = (is_true) ? (uint32_t)(reg32 | SW_SENS_ENABLE_NEGATIVE_EDGE_MASK) : (uint32_t)( reg32 & ~SW_SENS_ENABLE_NEGATIVE_EDGE_MASK );

    SW_IF_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

 
void mbmcs_std_2state_switch_sens_positive_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_true)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    reg32 = (is_true) ? (uint32_t)(reg32 | SW_SENS_ENABLE_POSITIVE_EDGE_MASK) : (uint32_t)( reg32 & ~SW_SENS_ENABLE_POSITIVE_EDGE_MASK);

    SW_IF_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}


void mbmcs_std_2state_switch_irq_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_true)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    reg32 = (is_true) ? (reg32 | SW_IF_IRQ_ENABLE_MASK) : ( reg32 & ~SW_IF_IRQ_ENABLE_MASK);

    SW_IF_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}


int mbmcs_std_2state_switch_get_flags(const mbmcs_std_2state_switch_t * const self_p, mbmcs_std_2state_switch_status_t * const stat_p)
{
    if( NULL == stat_p ) {
    return EINVAL;  
    } else {    
    mbmcs_std_2state_switch_status_t stat = { 0 };
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    DBMS5(stderr, "mbmcs_std_2state_switch_get_flags : reg32=%08x" EOL_CRLF, reg32);
    
    
#if 0
    stat.f.current_signal = (reg32 & SW_CURRENT_LEVEL_MASK) ? ~0 : 0;
#else
    if(reg32 & SW_CURRENT_LEVEL_MASK) {
        stat.f.current_signal = ~0;
    } else {
        stat.f.current_signal = 0;
    }
#endif
#if 0
    stat.f.positive_edge  = (reg32 & SW_POSITIVE_EDGE_DETECTIVE_MASK) ? 0x1 : 0;
    stat.f.negative_edge  = (reg32 & SW_NEGATIVE_EGDE_DETECTIVE_MASK) ? 0x1 : 0;
#else
    if((reg32 & SW_POSITIVE_EDGE_DETECTIVE_MASK)!=0) {
        stat.f.positive_edge =~0;
    } else {
        stat.f.positive_edge = 0;
    }
    if((reg32 & SW_NEGATIVE_EGDE_DETECTIVE_MASK)!=0) {
        stat.f.negative_edge = ~0;
    } else {
        stat.f.negative_edge = 0;
    }
#endif
    DBMS3( stderr, "stat.f.current_signal=%d" EOL_CRLF, stat.f.current_signal);
    DBMS3( stderr, "stat.f.positive_edge=%d" EOL_CRLF, stat.f.positive_edge);
    DBMS3( stderr, "stat.f.negative_edge=%d" EOL_CRLF, stat.f.negative_edge);

    *stat_p = stat;
    }

    return 0;
}

 
void mbmcs_std_2state_switch_clear_detective_egde_flags(const mbmcs_std_2state_switch_t * const self_p)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    reg32 &= ~SW_EDGE_DETECTIVE_MASK;

    SW_IF_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}


uint32_t _mbmcs_std_2state_switch_get_registers(const mbmcs_std_2state_switch_t * const self_p)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    return reg32;
}


void _mbmcs_std_2state_switch_dump_registers(const mbmcs_std_2state_switch_t * const self_p)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    DMSG( stderr, "module enable:%x" EOL_CRLF, (reg32 & SW_IF_MODULE_ENABLE_MASK ? 0x1 : 0));
    DMSG( stderr, "irq_enable: %x" EOL_CRLF, (reg32 & SW_IF_IRQ_ENABLE_MASK ? 0x1 : 0));
    DMSG( stderr, "detective positive edge:%x" EOL_CRLF, (reg32 & SW_POSITIVE_EDGE_DETECTIVE_MASK ? 0x1 : 0));
    DMSG( stderr, "detective negative edge:%x" EOL_CRLF, (reg32 & SW_NEGATIVE_EGDE_DETECTIVE_MASK ? 0x1 : 0));
    DMSG( stderr, "current level:%x" EOL_CRLF, (reg32 & SW_NEGATIVE_EGDE_DETECTIVE_MASK ? 0x1 : 0));
    DMSG( stderr, "sensitive positive edge enable:%x" EOL_CRLF,
      (reg32 & SW_SENS_ENABLE_POSITIVE_EDGE_MASK) ? 0x1 : 0);
    DMSG( stderr, "sensitive negative edge enable:%x" EOL_CRLF,
      (reg32 & SW_SENS_ENABLE_NEGATIVE_EDGE_MASK) ? 0x1 : 0);
    DMSG( stderr, "edge counter enable:%x" EOL_CRLF,
      (reg32 & SW_EDGE_COUNTER_ENABLE_MASK) ? 0x1 : 0);
    DMSG( stderr, "egde counter value:%04x" EOL_CRLF,
        (reg32 & (SW_EDGE_COUNTER_VALUE_MASK >> SW_EDGE_COUNTER_VALUE_SHIFT)));

    return;
}

void mbmcs_std_2state_switch_edge_counter_enable(const mbmcs_std_2state_switch_t * const self_p, const uint8_t is_true) {
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    reg32 = (is_true) ? (reg32 | SW_EDGE_COUNTER_ENABLE_MASK) : ( reg32 & ~SW_EDGE_COUNTER_ENABLE_MASK);

    SW_IF_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

void mbmcs_std_2state_switch_edge_counter_clear(const mbmcs_std_2state_switch_t * const self_p)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    reg32 |=  SW_EDGE_COUNTER_CLEAR_MASK;

    SW_IF_OP_STAT_REG(self_p->base_addr) = reg32;

    return;
}

uint16_t mbmcs_std_2state_switch_get_edge_counter_value(const mbmcs_std_2state_switch_t * const self_p)
{
    uint32_t reg32 = SW_IF_OP_STAT_REG(self_p->base_addr);

    reg32 >>= SW_EDGE_COUNTER_VALUE_SHIFT;

    return (reg32 & SW_EDGE_COUNTER_VALUE_BIT);
}

uint64_t mbmcs_std_2state_switch_get_monotonic_timer(const mbmcs_std_2state_switch_t * const self_p)
{
    const uint64_t lsb32 = SW_IF_MONOTONIC_TIMER64_LSB32_REG(self_p->base_addr);
    const uint64_t msb32 = SW_IF_MONOTONIC_TIMER64_MSB32_REG(self_p->base_addr);

    return ((msb32 << 32) | lsb32);
}
