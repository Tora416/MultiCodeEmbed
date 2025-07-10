




#include "../lcd_header.h"

#define ROW (0x0F<<17)   
#define COL (0x0F<<21)   

int main()
{
    int val;
    IODIR1 = IODIR1 & ~(ROW);

    IODIR1 = IODIR1 | (COL);




    lcd_config();
    while(1)
    {
        val = (IOPIN1 & ROW); 
        val = val >> 17;





    




        if(val == 0x0E)
        {
            lcd_str("row1");
            delay(500);
        }



        if(val == 0x0D)
        {
            lcd_str("row2");
            delay(500);
        }



        if(val == 0x0B)
        {
            lcd_str("row3");
            delay(500);
        }



        if(val == 0x07)
        {
            lcd_str("Row4");
            delay(500);
        }
       








        lcd_cmd(0x01);
    
    }   
}
