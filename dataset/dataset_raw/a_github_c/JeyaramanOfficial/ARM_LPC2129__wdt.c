







#include<lpc21xx.h>

void delay(int );
void blink_led(int);

int main()
{
    IODIR1 |= 0xFF<<17;
    WDMOD = (1<<1) | (1<<0);   
    WDTC = 0xFFFFFF;
    blink_led(24);
    WDFEED = 0xAA; 
    WDFEED = 0x55;
    while(1)
    {
        blink_led(17);
    }
}

void delay(int ct)
{
    for(int i=0;i<ct;i++)
    {
        for(int j=0;j<6000;j++)
        {}
    }
}

void blink_led(int led)
{
    IOSET1 = 1<<led;
        delay(500);
        IOCLR1 = 1<<led;
        delay(500);
}
