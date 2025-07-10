









#include "../lcd_header.h"

#define ROW (0x0F<<21)    
#define COL (0x0F<<17)    
void row_key(void);
void col_key1(void);
void col_key2(void);
void col_key3(void);
void col_key4(void);
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
                col_key1();  
                break;
            case 0x0D:
                col_key2();  
                break;
            case 0x0B:
                col_key3();  
                break;
            case 0x07:
                col_key4();  
                break;



        }
}

void col_key1(void)
{
        int val;
        IODIR1 = IODIR1 & ~(COL);  
        IODIR1 = IODIR1 | (ROW);  
        val = (IOPIN1 & COL); 
        val = val >> 17;
        switch(val)
        {
            case 0x0E: 
                lcd_data('1');
                delay(500);
                break;
            case 0x0D:
                lcd_data('2');
                delay(500);
                break;
            case 0x0B:
                lcd_data('3');
                delay(500);
                break;
            case 0x07:
                lcd_data('+');
                delay(500);
                break;
                        
        }
}

void col_key2(void)
{
        int val;
        IODIR1 = IODIR1 & ~(COL);  
        IODIR1 = IODIR1 | (ROW);  
        val = (IOPIN1 & COL); 
        val = val >> 17;
        switch(val)
        {
            case 0x0E: 
                lcd_data('4');
                delay(500);
                break;
            case 0x0D:
                lcd_data('5');
                delay(500);
                break;
            case 0x0B:
                lcd_data('6');
                delay(500);
                break;
            case 0x07:
                lcd_data('-');
                delay(500);
                break;
                    
        }
}
void col_key3(void)
{
        int val;
        IODIR1 = IODIR1 & ~(COL);  
        IODIR1 = IODIR1 | (ROW);  
        val = (IOPIN1 & COL); 
        val = val >> 17;
        switch(val)
        {
            case 0x0E: 
                lcd_data('7');
                delay(500);
                break;
            case 0x0D:
                lcd_data('8');
                delay(500);
                break;
            case 0x0B:
                lcd_data('9');
                delay(500);
                break;
            case 0x07:
                lcd_data('*');
                delay(500);
                break;
                        
        }
}

void col_key4(void)
{
        int val;
        IODIR1 = IODIR1 & ~(COL);  
        IODIR1 = IODIR1 | (ROW);  
        val = (IOPIN1 & COL); 
        val = val >> 17;
        switch(val)
        {
            case 0x0E: 
                lcd_data('#');
                delay(500);
                break;
            case 0x0D:
                lcd_data('0');
                delay(500);
                break;
            case 0x0B:
                lcd_data('=');
                delay(500);
                break;
            case 0x07:
                lcd_data('/');
                delay(500);
                break;
                        
        }
}





