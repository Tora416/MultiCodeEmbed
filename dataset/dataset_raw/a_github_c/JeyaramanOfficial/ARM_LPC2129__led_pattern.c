























#include<lpc21xx.h>
#define LED_ALL (0xff<<17)
#define LED1    (1<<17)         
#define LED2    (1<<18)         
void delay(int);

int main()
{
    IODIR1 = IODIR1 | LED_ALL;
    
    while(1)
    {
        for(int i=17; i<= 24;i++)
        {
        IOSET1 = 1<<i;
        delay(1000);
        }
        IOCLR1 = LED_ALL;
        delay(1000);
    }
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
