












#include<lpc21xx.h>
void delay(int );
void blink_LED(int );
void timer0_config(void);
void timer1_config(void);
void interrupt_config(void);

void nonvic_isr(void) __irq;


int main()
{
    IODIR1 = IODIR1 | (0xFF<<17);       
    IODIR0 |= (1<<11);
    timer1_config();
    timer0_config();
    interrupt_config();
    while(1)
    {
            blink_LED(24);
    }
}

void interrupt_config(void)
{
    PINSEL0 |= (1<<29);
    PINSEL0 &= ~(1<<28);                                                    
    VICIntSelect &= ~((1<<4)|(1<<5)|(1<<15));           
    
    VICDefVectAddr  = (long)nonvic_isr;
    
    VICIntEnable    = (1<<4)|(1<<5)|(1<<15) ;               
    EXTMODE = (1<<1);                                                       
    EXTPOLAR    = (1<<1);                                                       
}
void nonvic_isr(void) __irq
{
    blink_LED(17);
    T0IR = (1<<0);          
    T1IR = (1<<0);
    EXTINT  =(1<<1);
    VICVectAddr =   0x00000000;     

}


void timer0_config(void)
{
    T0PR = 14;
    T0MR0 = 4000000;                            
    T0MCR = (1<<0)|(1<<1);
    T0TCR = (1<<0);
}

void timer1_config(void)
{
    T1PR = 14;
    T1MR0 = 5000000;                            
    T1MCR = (1<<0)|(1<<1);
    T1TCR = (1<<0);
    
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
