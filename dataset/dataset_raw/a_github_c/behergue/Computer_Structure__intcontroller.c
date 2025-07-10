


#include "44b.h"
#include "intcontroller.h"

void ic_init(void)
{
    
    rINTMOD = 0x0; 
    rINTCON = 0x7; 
    rINTMSK = ~(0x0); 
}

int ic_conf_irq(enum enable st, enum int_vec vec)
{
    int conf = rINTCON;

    if (st != ENABLE && st != DISABLE)
        return -1;

    if (vec == VEC)
    {
        
        
        unsigned int b = 1;
        b <<= 2;

        conf &= ~b;
    }
    else
    {
        
        
        unsigned int b = 1;
        b <<= 2;

        conf |= b;
    }

    if (st == ENABLE)
    {
        
        
        unsigned int b = 1;
        b <<= 1;

        conf &= ~b;
    }
    else
    {
        
        
        unsigned int b = 1;
        b <<= 1;

        conf |= b;
    }

    rINTCON = conf;
    return 0;
}

int ic_conf_fiq(enum enable st)
{
    int ret = 0;

    if (st == ENABLE)
    {
        
        
        unsigned int b = 1;

        ret &= ~b;
    }
    else if (st == DISABLE)
    {
        
        
        unsigned int b = 1;

        ret |= b;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

int ic_conf_line(enum int_line line, enum int_mode mode)
{
    unsigned int bit = INT_BIT(line);

    if (line < 0 || line > 26)
        return -1;

    if (mode != IRQ && mode != FIQ)
        return -1;

    if (mode == IRQ)
    {
        
        unsigned int b = 1;
        b <<= bit;
        
        rINTMOD &= ~b;
    }
    else
    {
        
        unsigned int b = 1;
        b <<= bit;
        
        rINTMOD |= b;
    }

    return 0;
}

int ic_enable(enum int_line line)
{
    if (line < 0 || line > 26)
        return -1;

    
    unsigned int b = 1;
    b <<= (int) line;
    
    rINTMSK &= ~b;

    return 0;
}

int ic_disable(enum int_line line)
{
    if (line < 0 || line > 26)
        return -1;

    
    unsigned int b = 1;
    b <<= (int) line;
    
    rINTMSK |= b;
    
    return 0;
}

int ic_cleanflag(enum int_line line)
{
    int bit;

    if (line < 0 || line > 26)
        return -1;

    bit = INT_BIT(line);

    if (rINTMOD & bit)
    {
        
        
        
        unsigned int b = 1;
        b <<= bit;

        rI_ISPC |= b;
    }
    else
    {
        
        
        unsigned int b = 1;
        b <<= bit;

        rF_ISPC |= b;
    }

    return 0;
}



