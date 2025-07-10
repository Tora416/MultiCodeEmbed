

 
#include <stdint.h>
#include <stdio.h>
#include <errno.h>



#include "multios_stdlib.h"


#include "mbmcs_def.h"
#include "mbmcs_stdio.h"
#include "mbmcs_stdintrc.h"


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



#define MBMCS_STDINTRC_ENABLE_OUTPUT ((uint32_t)(0x1))
#define MBMCS_STDINTRC_IRQ_MASK ((uint32_t)(0xfffffffe))


extern int mbmcs_stdintrc_init(mbmcs_stdintrc_t *const, const uintptr_t)
    __attribute__ ((optimize("Os")));
extern int mbmcs_stdintrc_enable_output( const mbmcs_stdintrc_t *const, const uintptr_t)
    __attribute__ ((optimize("O2")));
extern int mbmcs_stdintrc_disable_output( const mbmcs_stdintrc_t *const, const uintptr_t)
    __attribute__ ((optimize("O2")));
extern int mbmcs_stdintrc_get_irq_flag( const mbmcs_stdintrc_t * const, const uintptr_t, uint32_t *const)
    __attribute__ ((optimize("O2")));
extern int mbmcs_stdintrc_clear_irq_flag( const mbmcs_stdintrc_t * const, const uintptr_t, const uint32_t)
    __attribute__ ((optimize("O2")));

#define INTR_REG(a, o) *((volatile unsigned int*)((intptr_t)(a) + (o)))


int mbmcs_stdintrc_init(mbmcs_stdintrc_t * const self_p, const uintptr_t base_addr)
{
    char str[MULTIOS_XTOA_HEX32_BUFSZ];

    DBMS5( stderr, "%s : base_addr=0x%s" EOL_CRLF, __func__, 
    multios_u32toahex( base_addr, str, MULTIOS_XTOA_HEX32_BUFSZ, NULL));
    DBMS5( stderr, "%s : MBMCS_MEMALIGN=%d" EOL_CRLF, __func__, MBMCS_MEMALIGN);
    DBMS5( stderr, "%s : MBMCS_EXTTEND_MODULE_MEMMAP_ADDR=0x%s" EOL_CRLF, __func__, 
    multios_u32toahex( MBMCS_EXTTEND_MODULE_MEMMAP_ADDR, str, MULTIOS_XTOA_HEX32_BUFSZ, NULL));

    if((base_addr < MBMCS_EXTTEND_MODULE_MEMMAP_ADDR) || ( base_addr & (MBMCS_MEMALIGN-1))) {
    return EINVAL;
    }

    self_p->base_addr = base_addr;

    return 0;
}


int mbmcs_stdintrc_enable_output( const mbmcs_stdintrc_t *const self_p, const uintptr_t addr_offs)
{
    const uint32_t reg32 =  (MBMCS_STDINTRC_ENABLE_OUTPUT | MBMCS_STDINTRC_IRQ_MASK);


    if( addr_offs & (MBMCS_MEMALIGN-1) ) {
    return EINVAL;
    }

    INTR_REG(self_p->base_addr, addr_offs) = reg32;

    return 0;
}


int mbmcs_stdintrc_disable_output( const mbmcs_stdintrc_t *const self_p, const uintptr_t addr_offs)
{
    if( addr_offs & (MBMCS_MEMALIGN-1) ) {
    return EINVAL;
    }

    INTR_REG(self_p->base_addr, addr_offs) = ~MBMCS_STDINTRC_ENABLE_OUTPUT;

    return 0;
}


int mbmcs_stdintrc_get_irq_flag( const mbmcs_stdintrc_t * const self_p, const uintptr_t addr_offs, uint32_t *const bitflags_p)
{
    if( ( addr_offs & (MBMCS_MEMALIGN-1)) || ( NULL == bitflags_p ) ) {
    return EINVAL;
    }

    *bitflags_p = INTR_REG(self_p->base_addr, addr_offs);

    return 0;
}


int mbmcs_stdintrc_clear_irq_flag( const mbmcs_stdintrc_t * const self_p, const uintptr_t addr_offs, const uint32_t clrbitflags)
{
    uint32_t reg32;
    uint32_t intr_enable;

    if( addr_offs & (MBMCS_MEMALIGN-1) ) {
    return EINVAL;
    }

    reg32 = INTR_REG(self_p->base_addr, addr_offs);
    intr_enable = reg32 & MBMCS_STDINTRC_ENABLE_OUTPUT;
    reg32 &=  ~clrbitflags | intr_enable;
    INTR_REG(self_p->base_addr, addr_offs) = reg32;

    IFDBG5THEN {
    DBMS5( stderr, "%s : clrbitflags = 0x%08s" EOL_CRLF, __FUNCTION__, clrbitflags);
    DBMS5( stderr, "%s : setdata = 0x%08x" EOL_CRLF, __FUNCTION__, reg32);
    }

    return 0;
}
