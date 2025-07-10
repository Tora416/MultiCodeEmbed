








#include<lpc21xx.h>
void delay(int );
void blink_LED(int );
void timer0_config(void);
void interrupt_config(void);
void timer0_isr1(void) __irq;               

int main()
{
    IODIR1 = IODIR1 | (0xFF<<17);       
    timer0_config();
    interrupt_config();
    while(1)
    {
            blink_LED(24);
    }
}

void interrupt_config(void)
{
    VICIntSelect &= ~(1<<4);            
    VICVectCntl2    = (1<<5)|4;         
    VICVectAddr2    = (long)timer0_isr1;        
    VICIntEnable    = (1<<4);               
}

void timer0_isr1(void) __irq
{
    blink_LED(17);
    T0IR = (1<<0);          
    VICVectAddr =   0x00000000;     
}

void timer0_config(void)
{
    T0PR = 14;
    T0MR0 = 2000000;
    T0MCR = (1<<0)|(1<<1);
    T0TCR = (1<<0);
}

void blink_LED(int led)
{
    IOSET1 = 1<<led;
    delay(300);             
    IOCLR1 = 1<<led;
    delay(300);             
}

void delay(int ct)
{
    int i,j;
    for(i=0;i<ct;++i)
    {
        for(j=0;j<6000;++j)             
        {}
    }
}
