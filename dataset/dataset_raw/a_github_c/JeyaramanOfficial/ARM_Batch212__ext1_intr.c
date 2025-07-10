#include<lpc21xx.h>
void delay(int );
void blink_LED(int );
void intr_config(void);
void eint1_isr(void) __irq;
int main()
{
    IODIR1 |= (0xFF<<17);
    intr_config();
    while(1)
    {
        blink_LED(24);
    }
}

void intr_config(void)
{
    PINSEL0 |= (1<<29);
    PINSEL0 &= ~(1<<28);    
    
    VICIntSelect &= ~(1<<15);       
    VICVectCntl1    = (1<<5)| 15;   
    VICVectAddr1    =   (long)eint1_isr;
    VICIntEnable = 1<<15;
    EXTMODE = (1<<1);       
    EXTPOLAR    = (1<<1);       

}

void eint1_isr(void) __irq
{
    blink_LED(17);
    EXTINT  = (1<<1);
    VICVectAddr = 0;
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
