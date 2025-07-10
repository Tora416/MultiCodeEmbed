

#include<lpc21xx.h>
#define LED_ALL (0xFF<<17)
void delay(int );
void blink_led(int );

int main()
{
    IODIR1 = IODIR1 | LED_ALL ;  
    IODIR1 = IODIR1 & ~(1<<25);  




    while(1)
    {
        if(IOPIN1 & (1<<25))
        {
            IOSET1 = 0x0F<<17;
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
