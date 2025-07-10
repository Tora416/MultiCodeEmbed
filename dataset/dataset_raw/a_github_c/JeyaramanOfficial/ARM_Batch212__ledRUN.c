#include<LPC21xx.h>       










    
void delay(int);

int main()
{
    IODIR1 = IODIR1 | (0xFF<<17);
                                    
    while(1)
    {
        for(int led =17;led <= 24; led++)
        {
            IOSET1 = 1<<led;
            delay(100);
            IOCLR1 = 1<<led;
            delay(100);
        }
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
