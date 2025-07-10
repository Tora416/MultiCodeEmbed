


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
        
        conf &= ~(1 <<2);

    else
        conf |= (1 << 2);
        

    if (st == ENABLE)
        conf &= ~(1 << 1);
        
    else
        conf |= (1 << 1);
        

    rINTCON = conf;
    return 0;
}

int ic_conf_fiq(enum enable st)
{
    int ret = 0;

    if (st == ENABLE)
        rINTCON &= ~1;
        
    else if (st == DISABLE)
        rINTCON |= 1;
        
    else
        ret = -1;

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
        
        rINTMOD &= ~bit;

    else
        
        rINTMOD |= bit;
    return 0;
}

int ic_enable(enum int_line line)
{
    if (line < 0 || line > 26)
        return -1;
    rINTMSK &= ~(1 << line);
    

    return 0;
}

int ic_disable(enum int_line line)
{
    if (line < 0 || line > 26)
        return -1;

    rINTMSK |= (1 << line);
    
    
    return 0;
}

int ic_cleanflag(enum int_line line)
{
    int bit;

    if (line < 0 || line > 26)
        return -1;

    bit = INT_BIT(line);

    if (rINTMOD & bit)
        
        
        rF_ISPC |= bit;
    else
        rI_ISPC |= bit;
        
        
    return 0;
}



