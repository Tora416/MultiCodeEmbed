#include "..\lcd_header.h"

int main()
{
    char var;
    PINSEL0 |= (1<<0)|(1<<2);   
    PINSEL0 &= ~((1<<1)|(1<<3));
    lcd_config();
    U0LCR = (1<<7);     
    U0DLL = 97;             
    U0DLM = 0;
    U0LCR &= ~(1<<7);   
    U0LCR = (1<<0)|(1<<1); 
    
    while(1)
    {
        while(!(U0LSR & (1<<0)));   
            var = U0RBR;            
            lcd_data(var);
    }
}


















