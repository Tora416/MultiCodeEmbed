






#include<LPC21xx.h>
void pll_48MHz(void);
void pll_36MHz(void);
void pll_12MHz(void);
void blink_led(int );
void delay_ms(int );
int count = 0;

int main()
{
    IODIR1 |= (0xFF<<17);
    while(1)
    {
        IOSET1 = 0xFF<<17;          
        delay_ms(500);
        IOCLR1 = 0xFF<<17;
        delay_ms(500);
        count++;
        if(count >= 10 && count<20)
        {
            pll_36MHz();                    
        }
        if (count >= 20 && count<25)
        { 
            pll_12MHz();                
        } else if(count >= 25)
        {
            pll_48MHz();
        }
    
    }
}

void pll_36MHz(void)
{
    PLLCON = 1<<0;              
    PLLFEED = 0xAA;
    PLLFEED = 0x55;             
    PLLCFG = (1<<6)| 2; 
    PLLCFG &= ~(1<<5);
    while(!(PLLSTAT & (1<<10)));            
    PLLCON = (1<<1)|(1<<0);         
    PLLFEED = 0xAA;
    PLLFEED = 0x55;             
}

void pll_48MHz(void)
{
    PLLCON = 1<<0;              
    PLLFEED = 0xAA;
    PLLFEED = 0x55;             
    PLLCFG = (1<<5)| 3; 
    PLLCFG &= ~(1<<5);
    while(!(PLLSTAT & (1<<10)));            
    PLLCON = (1<<1)|(1<<0);         
    PLLFEED = 0xAA;
    PLLFEED = 0x55;             
}

void pll_12MHz(void)
{
    PLLCON = 1<<0;              
    PLLFEED = 0xAA;
    PLLFEED = 0x55;             
    PLLCFG = (1<<6)| (1<<5) | 0;    
    while(!(PLLSTAT & (1<<10)));            
    PLLCON = (1<<1)|(1<<0);         
    PLLFEED = 0xAA;
    PLLFEED = 0x55;             
}


void blink_led(int led)
{
        IOSET1 = 1<<led;  
        delay_ms(100);
        IOCLR1 = 1<<led;   
        delay_ms(100);
}

void delay_ms(int ct)
{
    int i,j;
    for(i=0;i<ct;++i)
    {
        for(j=0;j<6000;++j)
        {}
    }
}
