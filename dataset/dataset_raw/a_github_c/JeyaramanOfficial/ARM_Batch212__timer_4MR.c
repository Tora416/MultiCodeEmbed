






#include<lpc21xx.h>

int main()
{
    IODIR1 = IODIR1 | (0xFF<<17);       
    T0PR = 14;                                          
    T0MR0 = 1000000;                                
    T0MR1 = 2000000;                                
    T0MR2 = 3000000;                                
    T0MR3   = 4000000;                              
    T0MCR   = (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<10);      
    T0TCR   = (1<<0);                                   
    while(1)
    {
        if(T0IR & (1<<0))                           
        {
            IOSET1 = (1<<17);
            T0IR = 1<<0;                                
        }
        
        if(T0IR & (1<<1))                           
        {
            IOCLR1 = (1<<17);
            T0IR = 1<<1;                                
        }
        if(T0IR & (1<<2))                           
        {
            IOSET1 = (1<<24);
            T0IR = 1<<2;                                
        }
        
        if(T0IR & (1<<3))                           
        {
            IOCLR1 = (1<<24);
            T0IR = 1<<3;                                
        }
    }
}
