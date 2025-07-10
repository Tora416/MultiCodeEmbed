


#include<lpc21xx.h>

void delay(int);



int main()
{
    IODIR1 = IODIR1 | (1<<17)|(1<<18);
    while(1)
    {
        IOSET1 = (1<<17)|(1<<18);
        delay(1000);
        IOCLR1 = (1<<17)|(1<<18);
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
