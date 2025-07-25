


#include<LPC21xx.h>
#define LED_ALL (0xFF<<17)

void blink_led(int);
void delay(int);

int main()
{
    IODIR1 = IODIR1 | LED_ALL ;  
    T0PR = 14;
    T0MR0 = 2000000;
    T0MCR = (1<<0)|(1<<1);  
    T0TCR = (1<<1);     
    T0TCR = (1<<0);  
    while(1)
    {
        if(T0IR & (1<<0))  
        {
            blink_led(17);
            T0IR = (1<<0); 
        }
    }
    
}

void blink_led(int led)
{
        IOSET1 = 1<<led;  
        delay(100);
        IOCLR1 = 1<<led;   
        delay(100);
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
