



        
#include "../lcd_header.h"
#define ROWS (0x0F<<21)
#define COLS (0x0F<<17)

int main()
{
    int val;



    IODIR1 = IODIR1 & ~ROWS;        
    IODIR1 = IODIR1 | COLS;         
    lcd_config();
    while(1)
    {
        val = IOPIN1 & ROWS;        
        val = val >> 21;
        switch(val)
        {
            case 0x0E:  lcd_str("r1");  delay(300); break;
            case 0x0D:  lcd_str("r2");  delay(300); break;
            case 0x0B:  lcd_str("r3");  delay(300); break;
            case 0x07:  lcd_str("r4");  delay(300); break;
        }
    }
}
