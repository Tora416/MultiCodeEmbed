




#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "mbmcs_stdio.h"
#include "mbmcs_YSM-430AXXA_35_7SEGLED.h"


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

#define MBMCS_EXTTEND_MODULE_MEMMAP_ADDR (0xC0000000)
#define MBMCS_MEMALIGN (4)


#define SEGLED_OP_AND_HEX_REG(a) *((volatile uint32_t*)((uintptr_t)(a) + 0x0))
#define SEGLED_ASCII_REG(a) *((volatile uint32_t*)((uintptr_t)(a) + 0x4))

#define SEG7X4DIGIT_MASK (0x0000ffff)
#define SEG7X4DOT_SHIFT  (16)
#define SEG7X4DOT_MASK   (((uint32_t)0xf) << SEG7X4DOT_SHIFT)
#define SEG7X4COLON_SHIFT (20)
#define SEG7X4COLON_MASK (((uint32_t)0x1) << SEG7X4COLON_SHIFT)
#define SEG7X4APOS_SHIFT (21)
#define SEG7X4APOS_MASK  (((uint32_t)0x1) << SEG7X4APOS_SHIFT)
#define SEG7X4TEST_SHIFT (30)
#define SEG7X4TEST_MASK  (((uint32_t)0x1) << SEG7X4TEST_SHIFT )
#define SEG7X4OFF_SHIFT (31)
#define SEG7X4OFF_MASK   (((uint32_t)0x1) << SEG7X4OFF_SHIFT )
#define SEG7X4SELASCII_SHIFT (29)
#define SEG7X4SELASCII_MASK (((uint32_t)0x1) << SEG7X4SELASCII_SHIFT )
#define SEG7X4ASCII_MASK (0xffffffff)


extern int mbmcs_ysm_430axxa_35_7seg4led_init(mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uintptr_t base_addr)
    __attribute__ ((optimize("Os")));
extern void mbmcs_ysm_430axxa_35_7seg4led_write_hex_digit(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint16_t data16)
    __attribute__ ((optimize("O2")));
extern void mbmcs_ysm_430axxa_35_7seg4led_write_dot(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t dots_bit)
    __attribute__ ((optimize("O2")));
extern void mbmcs_ysm_430axxa_35_7segled_write_colon(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern void mbmcs_ysm_430axxa_35_7seg4led_write_apos(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern int mbmcs_ysm_430axxa_35_7seg4led_test(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern int mbmcs_ysm_430axxa_35_7seg4led_on(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern void mbmcs_ysm_430axxa_35_7seg4led_ascii_mode(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
    __attribute__ ((optimize("O2")));
extern int mbmcs_ysm_430axxa_35_7seg4led_write_ascii_digit(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const char * const str)
    __attribute__ ((optimize("O2")));
extern int mbmcs_ysm_430axxa_35_7seg4led_destroy(mbmcs_ysm_430axxa_35_7seg4led_t *const self_p)
    __attribute__ ((optimize("O2")));




int mbmcs_ysm_430axxa_35_7seg4led_init(mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uintptr_t base_addr)
{
    if((base_addr < MBMCS_EXTTEND_MODULE_MEMMAP_ADDR) ||  ( base_addr % MBMCS_MEMALIGN )) {
    return EINVAL;
    }
    self_p->base_addr = base_addr;
 
     return 0;
}


void mbmcs_ysm_430axxa_35_7seg4led_write_hex_digit(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint16_t data16)
{
    uint32_t reg32 = SEGLED_OP_AND_HEX_REG(self_p->base_addr);
    
    reg32 &= ~SEG7X4DIGIT_MASK;
    reg32 |= SEG7X4DIGIT_MASK & data16;

    SEGLED_OP_AND_HEX_REG(self_p->base_addr) = reg32;

    return ;
}


void mbmcs_ysm_430axxa_35_7seg4led_write_dot(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t dots_bit)
{
    uint32_t reg32 = SEGLED_OP_AND_HEX_REG(self_p->base_addr);
    
    reg32 &= ~SEG7X4DOT_MASK;
    reg32 |= (SEG7X4DOT_MASK & ((uint32_t)(dots_bit) << SEG7X4DOT_SHIFT));

    SEGLED_OP_AND_HEX_REG(self_p->base_addr) = reg32;

    return;
}


void mbmcs_ysm_430axxa_35_7segled_write_colon(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
{
    uint32_t reg32 = SEGLED_OP_AND_HEX_REG(self_p->base_addr);
    
    reg32 &= ~SEG7X4COLON_MASK;
    reg32 |= (is_on) ? SEG7X4COLON_MASK : 0x0;

    SEGLED_OP_AND_HEX_REG(self_p->base_addr) = reg32;

    return;
}


void mbmcs_ysm_430axxa_35_7seg4led_write_apos(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
{
    uint32_t reg32 = SEGLED_OP_AND_HEX_REG(self_p->base_addr);
    
    reg32 &= ~SEG7X4APOS_MASK;
    reg32 |= (is_on) ? SEG7X4APOS_MASK : 0x0;

    SEGLED_OP_AND_HEX_REG(self_p->base_addr) = reg32;

    return;
}


int mbmcs_ysm_430axxa_35_7seg4led_test(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
{
    uint32_t reg32 = SEGLED_OP_AND_HEX_REG(self_p->base_addr);
    
    reg32 &= ~SEG7X4TEST_MASK;
    reg32 |= (is_on) ? SEG7X4TEST_MASK : 0x0;

    SEGLED_OP_AND_HEX_REG(self_p->base_addr) = reg32;

    return 0;
}


int mbmcs_ysm_430axxa_35_7seg4led_on(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
{
    uint32_t reg32 = SEGLED_OP_AND_HEX_REG(self_p->base_addr);
    
    reg32 &= ~SEG7X4OFF_MASK;
    reg32 |= (is_on) ? 0x0 : SEG7X4OFF_MASK;

    SEGLED_OP_AND_HEX_REG(self_p->base_addr) = reg32;

    return 0;
}


void mbmcs_ysm_430axxa_35_7seg4led_ascii_mode(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const uint8_t is_on)
{
    uint32_t reg32 = SEGLED_OP_AND_HEX_REG(self_p->base_addr);
    
    reg32 &= ~SEG7X4SELASCII_MASK;
    reg32 |= (is_on) ? SEG7X4SELASCII_MASK : 0x0;
    DBMS3( stderr, "ASCII_MODE=0x%08x" EOL_CRLF, reg32);

    SEGLED_OP_AND_HEX_REG(self_p->base_addr) = reg32;

    return;
}


int mbmcs_ysm_430axxa_35_7seg4led_write_ascii_digit(const mbmcs_ysm_430axxa_35_7seg4led_t *const self_p, const char * const str)
{
    uint32_t reg32 = 0;
    const size_t length = strlen(str);
    size_t n;

    if( !(length <= 4) ) {
    return EINVAL;
    }

    for( n=0; n<length; ++n) {
        reg32 <<= 8;
    reg32 |= 0xff & str[n];
    }

    SEGLED_ASCII_REG(self_p->base_addr) = reg32;

    return 0;
}


int mbmcs_ysm_430axxa_35_7seg4led_destroy(mbmcs_ysm_430axxa_35_7seg4led_t *const self_p)
{
    (void)self_p;

    return 0;
}

