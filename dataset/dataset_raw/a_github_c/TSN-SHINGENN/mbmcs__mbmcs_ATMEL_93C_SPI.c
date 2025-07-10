


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "multios_sys_types.h"
#include "multios_unistd.h"


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


#if defined(_MULTIOS_DMSG_IS_UART)
#define EOL_CRLF "\n\r"
#else
#define EOL_CRLF "\n"
#endif


#include "mbmcs_platform.h"
#include "mbmcs_time.h"
#include "mbmcs_ATMEL_93C_SPI.h"

#define STATUS_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x0))
#define OP_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x0))
#define ADDR_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x4))
#define WRITE_DATA_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0x8))
#define READ_DATA_REG(a) *((volatile unsigned int*)((intptr_t)(a) + 0xC))

#define STATUS_X8_ADDRBIT_BIT ((uint32_t)0x3f)
#define STATUS_X8_ADDRBIT_SHIFT (0)
#define STATUS_X8_ADDRBIT_MASK (STATUS_X8_ADDRBIT_BIT << STATUS_X8_ADDRBIT_SHIFT)

#define STATUS_X16_ADDRBIT_BIT ((uint32_t)0x1f)
#define STATUS_X16_ADDRBIT_SHIFT (0)
#define STATUS_X16_ADDRBIT_MASK (STATUS_X16_ADDRBIT_MASK << STATUS_X16_ADDRBIT_SHFT)


#define OP_START_BIT ((uint32_t)0x1)
#define OP_START_SHIFT (0)
#define OP_START_MASK (OP_START_BIT << OP_START_SHIFT)

#define OP_OPCODE_BIT ((uint32_t)0x3)
#define OP_OPCODE_SHIFT (30)
#define OP_OPCODE_MASK (OP_OPCODE_BIT << OP_OPCODE_SHIFT)
#define OP_SUBOP_CODE_BIT ((uint32_t)0x3)
#define OP_SUBOP_CODE_SHIFT (28)
#define OP_SUBOP_MASK (OP_SUBOP_CODE_BIT << OP_SUBOP_CODE_SHIFT)

#define STAT_READY_BIT ((uint32_t)0x1)
#define STAT_READY_SHIFT (0)
#define STAT_READY_MASK (STAT_READY_BIT << STAT_READY_SHIFT)

#define STAT_X16MODE_BIT ((uint32_t)0x1)
#define STAT_X16MODE_SHIFT (15)
#define STAT_X16MODE_MASK (STAT_X16MODE_BIT << STAT_X16MODE_SHIFT)
#define STAT_BUSY_BIT ((uint32_t)0x1)
#define STAT_BUSY_SHIFT (4)
#define STAT_BUSY_MASK (STAT_BUSY_BIT << STAT_BUSY_SHIFT)
#define STAT_EINVAL_BIT ((uint32_t)0x1)
#define STAT_EINVAL_SHIFT (3)
#define STAT_EINVAL_MASK (STAT_EINVAL_BIT << STAT_EINVAL_SHIFT)
#define STAT_ETIMEDOUT_BIT ((uint32_t)0x1)
#define STAT_ETIMEDOUT_SHIFT (2)
#define STAT_ETIMEDOUT_MASK (STAT_ETIMEDOUT_BIT << STAT_ETIMEDOUT_SHIFT) 
#define STAT_EINVAL_MASK (STAT_EINVAL_BIT << STAT_EINVAL_SHIFT)
#define STAT_DONE_BIT ((uint32_t)0x1)
#define STAT_DONE_SHIFT (1)
#define STAT_DONE_MASK (STAT_DONE_BIT << STAT_DONE_SHIFT)



#define ATMEL93C_ADDRMASK 0x7f

#define ATMEL93C_READMASK 0xffff 

#define ATMEL93C_WRITEMASK 0xffff 


extern int mbmcs_atmel_93c_init( mbmcs_atmel_93c_spi_t * const self_p, const intptr_t base_addr, const enum_mbmcs_atmel_93c_series_t model)
    __attribute__ ((optimize("Os")));
extern int mbmcs_atmel_93c_set_vcc_attribute( mbmcs_atmel_93c_spi_t * const self_p, uint8_t vcc_is_exceed_4p5)
    __attribute__ ((optimize("Os")));

extern int mbmcs_atmel_93c_destroy( mbmcs_atmel_93c_spi_t * const self_p)
    __attribute__ ((optimize("Os")));

extern int mbmcs_atmel_93c_readx8( const mbmcs_atmel_93c_spi_t * const self_p, const uint16_t addr, uint8_t *const d8_p)
    __attribute__ ((optimize("O2")));
extern int mbmcs_atmel_93c_writex8( const mbmcs_atmel_93c_spi_t * const self_p, const uint16_t addr, const uint8_t d8)
    __attribute__ ((optimize("O2")));

extern int mbmcs_atmel_93c_erasex8( const mbmcs_atmel_93c_spi_t * const self_p, const uint16_t addr)
    __attribute__ ((optimize("O2")));

extern int mbmcs_atmel_93c_write_enable( const mbmcs_atmel_93c_spi_t * const self_p)
    __attribute__ ((optimize("O2")));
extern int mbmcs_atmel_93c_write_disable( const mbmcs_atmel_93c_spi_t * const self_p)
    __attribute__ ((optimize("O2")));

static int atmel_93c_ready_wait_timeout(const uint32_t addr)
    __attribute__ ((optimize("O2")));


int mbmcs_atmel_93c_init( mbmcs_atmel_93c_spi_t * const self_p, const intptr_t base_addr, const enum_mbmcs_atmel_93c_series_t model)
{
    size_t n;
    uint32_t rd32;
    
    mbmcs_atmel_93c_api_attr_t attr;

    self_p->base_addr = base_addr;

    if(atmel_93c_ready_wait_timeout(self_p->base_addr)) {
    DBMS1( stderr, "93c_init : module is not ready" EOL_CRLF);
    return EAGAIN;
    } 

#if 1
    for( n=0; mbmcs_atmel_93c_bit_depth_list[n].model != ATMEL_93C_EOD; ++n) {
    if( mbmcs_atmel_93c_bit_depth_list[n].model == model) {
        break;
    }
    }

    if(mbmcs_atmel_93c_bit_depth_list[n].model != ATMEL_93C46) {
    return ENOTSUP;
    }

    if(mbmcs_atmel_93c_bit_depth_list[n].model == ATMEL_93C_EOD) {
    return ENOTSUP;
    }
    self_p->model = model;

    
    rd32 = mbmcs_platform_read_register32(self_p->base_addr);

    
    attr.flags = 0;
    attr.f.datamode_is_x16 = ( rd32 & STAT_X16MODE_MASK ) ? 1 : 0;
    self_p->attr = attr;
#endif

    return 0;
}

int mbmcs_atmel_93c_set_vcc_attribute( mbmcs_atmel_93c_spi_t * const self_p, const uint8_t vcc_is_over_4p5)
{
    self_p->attr.f.vcc_is_over_4p5 = (vcc_is_over_4p5) ? 1 : 0;

    return 0;
}

#if 0

int mbmcs_atmel_93c_set_interrupt_callback( mbmcs_atmel_93c_spi_t * const self_p, void (*func)(mbmcs_atmel_93c_intr_t*))
{
    if( NULL == func ) {
    self_p->attr.f.use_interrupt = 0;
    self_p->intr_callback_func = NULL;
    self_p->interrupted = 0;
    return 0;
    } 

    

    self_p->attr.f.use_interrupt = 1;
    self_p->intr_callback_func = func;
    self_p->interrupted = 0;

    return ENOTSUP;
}
#endif

int mbmcs_atmel_93c_readx8( const mbmcs_atmel_93c_spi_t * const self_p, const uint16_t addr, uint8_t *const d8_p)
{
    uint32_t reg32;

    if( self_p->attr.f.datamode_is_x16) {
    DBMS1( stderr, "93c_readx8 : module invalid mode(valid x8)" EOL_CRLF);
    return EACCES;
    }

    if(atmel_93c_ready_wait_timeout(self_p->base_addr)) {
    DBMS1( stderr, "93c_readx8 : module is not ready" EOL_CRLF);
    return EAGAIN;
    } 

    reg32 = STATUS_REG(self_p->base_addr);
    if(reg32 & STAT_BUSY_MASK) {
    DBMS1( stderr, "93c_readx8 : is BUSY" EOL_CRLF);
    return EBUSY;
    }

    ADDR_REG(self_p->base_addr) = addr;

    reg32 &= ~(OP_OPCODE_MASK | OP_SUBOP_MASK); 
    reg32 |= ((OP_OPCODE_BIT & 0x2) << OP_OPCODE_SHIFT) | OP_START_MASK;

    STATUS_REG(self_p->base_addr) = reg32;

    
    while(!((reg32 = STATUS_REG(self_p->base_addr)) & STAT_DONE_MASK));

    if(reg32 & STAT_EINVAL_MASK) {
    DBMS1( stderr, "93c_readx8 : STAT_EINVAL" EOL_CRLF);
    return EINVAL;
    }
    if(reg32 & STAT_ETIMEDOUT_MASK) {
    DBMS1( stderr, "93c_readx8 : STAT_ETIMEDOUT" EOL_CRLF);
    return ETIMEDOUT;
    }

    *d8_p = (0xff & READ_DATA_REG(self_p->base_addr));

    return 0;    
}

int mbmcs_atmel_93c_writex8( const mbmcs_atmel_93c_spi_t * const self_p, const uint16_t addr, const uint8_t d8)
{
    uint32_t reg32;

    if( self_p->attr.f.datamode_is_x16) {
    DBMS1( stderr, "93c_writex8 : x16 access denaind" EOL_CRLF);
    return EACCES;
    }

    if(atmel_93c_ready_wait_timeout(self_p->base_addr)) {
    DBMS1( stderr, "93c_writex8 : module is not ready" EOL_CRLF);
    return EAGAIN;
    } 

    reg32 = STATUS_REG(self_p->base_addr);
    if(reg32 & STAT_BUSY_MASK) {
    DBMS1( stderr, "93c_writex8 : is BUSY" EOL_CRLF);
    return EBUSY;
    }

    ADDR_REG(self_p->base_addr) = addr;
    WRITE_DATA_REG(self_p->base_addr) = 0xff & d8;

    reg32 &= ~(OP_OPCODE_MASK | OP_SUBOP_MASK); 
    reg32 |= ((OP_OPCODE_BIT & 0x1) << OP_OPCODE_SHIFT) | OP_START_MASK;

    STATUS_REG(self_p->base_addr) = reg32;

    
    DBMS3( stderr, "93c_writex8 : pollog wait" EOL_CRLF);
    while(!((reg32 = STATUS_REG(self_p->base_addr)) & STAT_DONE_MASK));

    if(reg32 & STAT_EINVAL_MASK) {
    DBMS1( stderr, "93c_writex8 : STAT_EINVAL" EOL_CRLF);
    return EINVAL;
    }
    if(reg32 & STAT_ETIMEDOUT_MASK) {
    DBMS1( stderr, "93c_writex8 : STAT_EINVAL" EOL_CRLF);
    return ETIMEDOUT;
    }

    return 0;  
}

int mbmcs_atmel_93c_erasex8( const mbmcs_atmel_93c_spi_t * const self_p, const uint16_t addr)
{
    uint32_t reg32;

    if(atmel_93c_ready_wait_timeout(self_p->base_addr)) {
    DBMS1( stderr, "93c_erasex8 : module is not ready" EOL_CRLF);
    return EAGAIN;
    } 

    reg32 = STATUS_REG(self_p->base_addr);
    if(reg32 & STAT_BUSY_MASK) {
    DBMS1( stderr, "93c_erasex8 : is BUSY" EOL_CRLF);
    return EBUSY;
    }
    ADDR_REG(self_p->base_addr) = addr;

    reg32 &= ~(OP_OPCODE_MASK | OP_SUBOP_MASK);
    reg32 |= ((OP_OPCODE_BIT & 0x3) << OP_OPCODE_SHIFT); 
    reg32 |= OP_START_MASK;

    STATUS_REG(self_p->base_addr) = reg32;

    
    DBMS3( stderr, "93c_erasex8 : pollog wait" EOL_CRLF);
    while(!((reg32 = STATUS_REG(self_p->base_addr)) & STAT_DONE_MASK));

    if(reg32 & STAT_EINVAL_MASK) {
    DBMS1( stderr, "93c_erasex8 : STAT_EINVAL" EOL_CRLF);
    return EINVAL;
    }
    if(reg32 & STAT_ETIMEDOUT_MASK) {
    DBMS1( stderr, "93c_erasex8 : STAT_EINVAL" EOL_CRLF);
    return ETIMEDOUT;
    }

    return 0;  
}

int mbmcs_atmel_93c_write_enable( const mbmcs_atmel_93c_spi_t * const self_p)
{
    uint32_t reg32;

    if(atmel_93c_ready_wait_timeout(self_p->base_addr)) {
    DBMS1( stderr, "93c_write_enable : module is not ready" EOL_CRLF);
    return EAGAIN;
    } 

    reg32 = STATUS_REG(self_p->base_addr);
    if(reg32 & STAT_BUSY_MASK) {
    DBMS3( stderr, "93c_write_enable : is BUSY" EOL_CRLF);
    return EBUSY;
    }

    ADDR_REG(self_p->base_addr) = 0;

    
    reg32 &= ~(OP_OPCODE_MASK | OP_SUBOP_MASK); 
    reg32 |= (OP_SUBOP_MASK & (0x3 << OP_SUBOP_CODE_SHIFT)) | OP_START_MASK;

    STATUS_REG(self_p->base_addr) = reg32;

    
    while(!((reg32 = STATUS_REG(self_p->base_addr)) & STAT_DONE_MASK));

    if(reg32 & STAT_EINVAL_MASK) {
    DBMS1( stderr, "93c_write_enable : EINVAL" EOL_CRLF);
    return EINVAL;
    }
    if(reg32 & STAT_ETIMEDOUT_MASK) {
    DBMS1( stderr, "93c_write_enable : ETIMEDOUT" EOL_CRLF);
    return ETIMEDOUT;
    }

    return 0;
}

static int atmel_93c_ready_wait_timeout(const uint32_t addr)
{
    const unsigned int timeout_msec=10;
    unsigned int cnt;
    uint32_t reg32;

    for(cnt=timeout_msec; cnt!=0; --cnt) {
        if(!((reg32 = STATUS_REG(addr)) & STAT_READY_MASK)) {
        break;
    }
    multios_msleep(1);
    }
    if( cnt==0 && !reg32 ) {
    return -1;
    } 

    return 0;
}


int mbmcs_atmel_93c_write_disable( const mbmcs_atmel_93c_spi_t * const self_p)
{
    uint32_t reg32;

    if(atmel_93c_ready_wait_timeout(self_p->base_addr)) {
    DBMS1( stderr, "93c_write_disable : module is not ready" EOL_CRLF);
    return EAGAIN;
    } 

    reg32 = STATUS_REG(self_p->base_addr);
    if(reg32 & STAT_BUSY_MASK) {
    DBMS3( stderr, "93c_write_disable : is BUSY" EOL_CRLF);
    return EBUSY;
    }

    ADDR_REG(self_p->base_addr) = 0;

    reg32 &= ~(OP_OPCODE_MASK | OP_SUBOP_MASK); 
    reg32 |= OP_START_MASK;

    STATUS_REG(self_p->base_addr) = reg32;

    
    while(!((reg32 = STATUS_REG(self_p->base_addr)) & STAT_DONE_MASK));



    if(reg32 & STAT_EINVAL_MASK) {
    DBMS1( stderr, "93c_write_disable : EINVAL" EOL_CRLF);
    return EINVAL;
    }

    if(reg32 & STAT_ETIMEDOUT_MASK) {
    DBMS1( stderr, "93c_write_disable : ETIMEDOUT" EOL_CRLF);
    return ETIMEDOUT;
    }

    return 0;
}
