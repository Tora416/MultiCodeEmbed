#include<LPC21xx.h>       













    
void delay(int);

int main()
{
    int val;
    IODIR1 = IODIR1 | (0xFF<<17);
                                    
    while(1)
    {
        for(val =0x01;val <= 0xFF; val++)
        {
            IOSET1 = val<<17;
            delay(100);
            IOCLR1 = val<<17;
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
