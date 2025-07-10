



#include<lpc21xx.h>
#define LED_ALL (0xFF<<17)

void delay_ms(int );
void blink_led(int );
void timer1_isr(void)__irq;
void timer_config(void);
void intr_config(void);

int main()
{
        IODIR1 = IODIR1| LED_ALL;
        timer_config();
        intr_config();
        while(1)
        {
            blink_led(17);
        }
}

void timer_config(void)
{
    
        T1PR = 14;
        T1MR0 = 2000000;
        T1MCR = (1<<0)|(1<<1);
        T1TCR = (1<<0);
}

void intr_config(void)
{
    
        VICIntSelect = VICIntSelect & ~((1<<4)|(1<<5)); 
        VICVectCntl1 = (1<<5)|5;   
        VICVectAddr1 = (long)&timer1_isr;       
        VICIntEnable = (1<<4)|(1<<5);   
}
void timer1_isr(void)__irq
{
    IOSET1 = 1<<24;  
    delay_ms(100);
    IOCLR1 = 1<<24;   
    delay_ms(100);
    T1IR = 1<<0;            
    VICVectAddr = 0x00000000;  
    
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





