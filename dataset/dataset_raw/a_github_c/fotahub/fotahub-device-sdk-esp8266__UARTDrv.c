
#include "UARTDrv.h"

#include "MultiPartitionDemoFirmwareUpdateInfoSerialReader.h"
#include <user_interface.h>
#include <ets_sys.h>

static void ICACHE_FLASH_ATTR uart_recvTask(os_event_t *pEvent);

static uint8_t uartUnit;

void ICACHE_FLASH_ATTR one_uart_init(uint8_t unit, UartBautRate baudrate)
{
  uartUnit = unit;
  system_os_task(&uart_recvTask, uart_recvTaskPrio, uart_recvTaskQueue, uart_recvTaskQueueLen);
  
  UartDev.baut_rate = baudrate;
  uart_config(unit);
  
  ETS_UART_INTR_ENABLE();
}

static void ICACHE_FLASH_ATTR uart_recvTask(os_event_t *pEvent)
{
  if (pEvent->sig == uart_recvTaskSignal) 
  {
    
    uint32_t uartStatus = READ_PERI_REG(UART_STATUS(uartUnit));
    uint8_t rxFIFOLength = UART_RXFIFO_DATA_LEN(uartStatus);
    
    
    for ( int16_t __i = 0 ; __i < rxFIFOLength; __i++ )
    {
      uint32_t uartFifo = READ_PERI_REG(UART_FIFO(uartUnit));
      uint8_t rxChar = UART_RXFIFO_DATA(uartFifo);
      firmwareUpdateInfoReader_onCharacterReceived(rxChar);
    }
    
    
    WRITE_PERI_REG(UART_INT_CLR(uartUnit),UART_RXFIFO_FULL_INT_CLR | UART_RXFIFO_TOUT_INT_CLR);
    
    
    uart_rx_intr_enable(uartUnit);
  }
}
