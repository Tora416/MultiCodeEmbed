

#include "44b.h"
#include "leds.h"
#include "gpio.h"


#define LED1 0x01
#define LED2 0x02
#define BIT_LED1 9
#define BIT_LED2 10





static unsigned int status = 0;

void leds_init( void )
{
    
    

    leds_display( status );
}

void led1_on( void )
{
    status |=  LED1;
    leds_display( status );
}

void led1_off( void )
{
    status &=  ~LED1;
    leds_display( status );
}

void led2_on( void )
{
    status |=  LED2;
    leds_display( status );
}

void led2_off( void )
{
    status &=  ~LED2;
    leds_display( status );
}

void led1_switch( void )
{
    status ^= LED1;
    leds_display( status );
}

void led2_switch( void )
{
    status ^= LED2;
    leds_display( status );
}

void leds_switch( void ){
    status ^= (LED1 | LED2);
    leds_display( status );
}

void leds_display( unsigned int leds_status )
{
    status = leds_status;
    
    
    if( status & LED1 )
        
        
    else
        
        

    
    if( status & LED2 )
        
        
    else
        
        
}
