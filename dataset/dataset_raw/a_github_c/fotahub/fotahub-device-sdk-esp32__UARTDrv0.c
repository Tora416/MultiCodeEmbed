
#include "UARTDrv.h"

#include "freertos/FreeRTOS.h"
#include <stdlib.h>

static uart_port_t uartUnit;

void uart_init(uart_port_t unit, uart_config_t *config, uint8_t txPin, uint8_t rxPin)
{
  uartUnit = unit;
  
  uart_param_config(unit, config);
  
  uart_set_pin(unit, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  
  uart_driver_install(unit, UART_BUFFER_SIZE, UART_BUFFER_SIZE, 0, NULL, 0);
  
  uart_set_mode(unit, UART_MODE_UART);
}

void uart_recvTask(void)
{
  size_t rxDataLen = 0;
  if (uart_get_buffered_data_len(uartUnit, &rxDataLen) != ESP_OK) 
  {
    return;
  }
  if (rxDataLen == 0) 
  {
    return;
  }
  
  uint8_t *data = ((uint8_t *)(malloc(rxDataLen)));
  
  uart_read_bytes(uartUnit, data, ((uint32_t)(rxDataLen)), 100 / portTICK_RATE_MS);
  
  for ( int64_t __i = 0 ; __i < rxDataLen; __i++ )
  {
    firmwareUpdateInfoReader_onCharacterReceived(*(data + __i));
  }
  if (data != NULL) 
  {
    free(data);
  }
}
