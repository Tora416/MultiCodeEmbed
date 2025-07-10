



#include<lpc21xx.h>
#define LED_ALL (0xFF<<17)

void delay_ms(int );
void blink_led(int );
void timer0_isr(void)__irq;

int main()
{
        IODIR1 = IODIR1| LED_ALL;
        
        T0PR = 14;
        T0MR0 = 2000000;
        T0MCR = (1<<0)|(1<<1);
        T0TCR = (1<<0);
        
        VICIntSelect = VICIntSelect & ~(1<<4); 


        VICVectCntl1 = (1<<5)|4;   
        VICVectAddr1 = (long)&timer0_isr;       
        VICIntEnable = (1<<4);   
        while(1)
        {
            blink_led(17);
        }
}

void timer0_isr(void)__irq
{
    IOSET1 = 1<<24;  
    delay_ms(100);
    IOCLR1 = 1<<24;   
    delay_ms(100);
    T0IR = 1<<0;            
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





