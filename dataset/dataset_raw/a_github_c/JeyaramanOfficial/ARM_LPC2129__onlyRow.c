







#include "../lcd_header.h"

#define ROW (0x0F<<21)    
#define COL (0x0F<<17)    
void rows(void);
void row_key(void);
void col_key(void);
int main()
{
    




    lcd_config();
    while(1)
    {
        row_key();
    }   
}

void row_key(void)
{
        int val;
        IODIR1 = IODIR1 & ~(ROW);
        IODIR1 = IODIR1 | (COL);
    
        val = (IOPIN1 & ROW); 
        val = val >> 21;
        
        switch(val)
        {
            case 0x0E: 
                lcd_str("R1");
                delay(500);
                break;
            case 0x0D:
                lcd_str("R2");
                delay(500);
                break;
            case 0x0B:
                lcd_str("R3");
                delay(500);
                break;
            case 0x07:
                lcd_str("R4");
                delay(500);
                break;
            default:
                delay(1000);
                lcd_cmd(0x01);
        }
}

void col_key(void)
{
        int val;
        IODIR1 = IODIR1 & ~(COL);  
        IODIR1 = IODIR1 | (ROW);  
    
        val = (IOPIN1 & COL); 
        val = val >> 21;
        
        switch(val)
        {
            case 0x0E: 
                lcd_str("C1");
                delay(500);
                break;
            case 0x0D:
                lcd_str("C2");
                delay(500);
                break;
            case 0x0B:
                lcd_str("C3");
                delay(500);
                break;
            case 0x07:
                lcd_str("C4");
                delay(500);
                break;
            default:
                delay(1000);
                lcd_cmd(0x01);
            
        }

}

void rows(void)
{
        int val;
        IODIR1 = IODIR1 & ~(ROW);
        IODIR1 = IODIR1 | (COL);
    
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
        delay(1000);
        lcd_cmd(0x01);
}
