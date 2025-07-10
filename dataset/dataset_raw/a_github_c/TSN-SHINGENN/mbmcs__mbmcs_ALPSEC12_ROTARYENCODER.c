




#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>





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

#define MBMCS_EXTTEND_MODULE_MEMMAP_ADDR 0xC0000000
#define MBMCS_MEMALIGN 4



#include "mbmcs_ALPSEC12_ROTARYENCODER.h"

#define ENCODER_CTRL_REG(a) *((volatile uint32_t*)((uintptr_t)(a) + 0x0))

#define ENCODER_RIGHT_SHIFT (0)
#define ENCODER_RIGHT_MASK (((uint32_t)0xff) << ENCODER_RIGHT_SHIFT)
#define ENCODER_LEFT_SHIFT (8)
#define ENCODER_LEFT_MASK (((uint32_t)0xff) << ENCODER_LEFT_SHIFT)
#define ENCODER_FUNCTION_ENABLE ((uint32_t)(0x1) << 31)
#define ENCODER_FUNCTION_IRQ_OUTPUT ((uint32_t)(0x1) << 30)


extern int mbmcs_alpsec12_rotaryencoder_init(mbmcs_alpsec12_rotaryencoder_t *const, const uintptr_t)
    __attribute__ ((optimize("Os")));
extern void mbmcs_alpsec12_rotaryencoder_get_count(const mbmcs_alpsec12_rotaryencoder_t *const, uint8_t *const, uint8_t *const)
    __attribute__ ((optimize("O2")));
extern void mbmcs_alpsec12_rotaryencoder_set_module_enable(const mbmcs_alpsec12_rotaryencoder_t *const, const uint8_t)
    __attribute__ ((optimize("O2")));
extern void mbmcs_alpsec12_rotaryencoder_set_module_irq_enable(const mbmcs_alpsec12_rotaryencoder_t *const, const uint8_t)
    __attribute__ ((optimize("O2")));
extern void mbmcs_alpsec12_rotaryencoder_clear_counter(const mbmcs_alpsec12_rotaryencoder_t *)
    __attribute__ ((optimize("O2")));


int mbmcs_alpsec12_rotaryencoder_init(mbmcs_alpsec12_rotaryencoder_t *const self_p, const uintptr_t base_addr)
{
    if((base_addr < MBMCS_EXTTEND_MODULE_MEMMAP_ADDR) ||  ( base_addr % MBMCS_MEMALIGN )) {
    return EINVAL;
    }
    self_p->base_addr = base_addr;
 
    return 0;
}


void mbmcs_alpsec12_rotaryencoder_get_count(const mbmcs_alpsec12_rotaryencoder_t *const self_p, uint8_t *const left_p, uint8_t *const right_p)
{
    const uint32_t reg = ENCODER_CTRL_REG(self_p->base_addr);

    if(0) {
    volatile uint8_t left = (uint8_t)(( ENCODER_LEFT_MASK & reg ) >> ENCODER_LEFT_SHIFT);
    volatile uint8_t right= (uint8_t)(( ENCODER_RIGHT_MASK & reg ) >> ENCODER_RIGHT_SHIFT);
    
    
    mbmcs_printf("ENCODER reg = 0x%08x" EOL_CRLF, reg);
    mbmcs_printf("ENCODER_LEFT_MASK=0x%08x ENCODER_LEFT_SHIFT=0x%08x" EOL_CRLF,
            ENCODER_LEFT_MASK, ENCODER_LEFT_SHIFT);
    mbmcs_printf("left=%08x right=%02x" EOL_CRLF, left, right);
    }

    if( NULL != left_p ) {
     *left_p = 0xff & (uint8_t)(( ENCODER_LEFT_MASK & reg ) >> ENCODER_LEFT_SHIFT);
    
    }

    if( NULL != right_p ) {
    *right_p = 0xff & (uint8_t)(( ENCODER_RIGHT_MASK & reg ) >> ENCODER_RIGHT_SHIFT);
    
    }

    return;
}


void mbmcs_alpsec12_rotaryencoder_set_module_enable(const mbmcs_alpsec12_rotaryencoder_t *const self_p, const uint8_t is_on)
{
    uint32_t reg = ENCODER_CTRL_REG(self_p->base_addr);

    if(is_on) {
    reg |= ENCODER_FUNCTION_ENABLE;
    } else {
    reg &= ~ENCODER_FUNCTION_ENABLE;
    }

    reg &= ~( ENCODER_LEFT_MASK | ENCODER_RIGHT_MASK );

    ENCODER_CTRL_REG(self_p->base_addr) = reg;

    return;
}


void mbmcs_alpsec12_rotaryencoder_set_module_irq_enable(const mbmcs_alpsec12_rotaryencoder_t *const self_p, const uint8_t is_on)
{
    uint32_t reg = ENCODER_CTRL_REG(self_p->base_addr);

    if(is_on) {
    reg |= ENCODER_FUNCTION_IRQ_OUTPUT;
    } else {
    reg &= ~ENCODER_FUNCTION_IRQ_OUTPUT;
    }

    ENCODER_CTRL_REG(self_p->base_addr) = reg;

    return;
}


void mbmcs_alpsec12_rotaryencoder_clear_counter(const mbmcs_alpsec12_rotaryencoder_t *const self_p)
{
    uint32_t reg = ENCODER_CTRL_REG(self_p->base_addr);

    reg &= ~( ENCODER_LEFT_MASK | ENCODER_RIGHT_MASK );

    ENCODER_CTRL_REG(self_p->base_addr) = reg;

    return;
}
