#include<lpc21xx.h>

int main()
{


    int count=0;
    IODIR1 = IODIR1 | (0xFF<<17);       
    T0PR = 14;                                          
    T0MR0 = 2000000;                                
    T0MR1 = 4000000;                                
    T0MCR   = (1<<0)|(1<<3)|(1<<4);     
    T0TCR   = (1<<0);                                   
    while(1)
    {
        count++;
        if(T0IR & (1<<0))                           
        {
            IOSET1 = (0xFF<<17);
            T0IR = 1<<0;                                
        }
        
        if(T0IR & (1<<1))                           
        {
            IOCLR1 = (0xFF<<17);
            T0IR = 1<<1;                                
        }








    
    }
}
