
#include "UARTDefinitions.h"

uart_config_t const UART_BASIC_CONFIG_DEFAULT_FOR_115200_Bd = 
{
  .baud_rate = UART_BAUDRATE_115200, 
  .data_bits = UART_DATA_8_BITS, 
  .parity = UART_PARITY_DISABLE, 
  .stop_bits = UART_STOP_BITS_1, 
  .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, 
  .rx_flow_ctrl_thresh = 122
};

UARTPinConfig_t const UART0_PIN_CONFIG_DEFAULT = 
{
  .tx = GPIO_NUM_1, 
  .rx = GPIO_NUM_3, 
  .rts = GPIO_NUM_22, 
  .cts = GPIO_NUM_19
};


UARTPinConfig_t const UART1_PIN_CONFIG_DEFAULT = 
{
  .tx = GPIO_NUM_4, 
  .rx = GPIO_NUM_5, 
  .rts = GPIO_NUM_21, 
  .cts = GPIO_NUM_18
};


UARTPinConfig_t const UART2_PIN_CONFIG_DEFAULT = 
{
  .tx = GPIO_NUM_17, 
  .rx = GPIO_NUM_16, 
  .rts = GPIO_NUM_26, 
  .cts = GPIO_NUM_23
};
