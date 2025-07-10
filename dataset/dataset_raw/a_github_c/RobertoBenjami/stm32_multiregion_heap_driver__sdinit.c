
#include "stm32f4xx_hal.h"

#define SDRAM_BANK_ADDR                 ((uint32_t)0xD0000000)


#define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_16


#define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3

#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define REFRESH_COUNT       ((uint32_t)0x056A)   


void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
  __IO uint32_t tmpmrd =0;
  FMC_SDRAM_CommandTypeDef Command;
  
  Command.CommandMode       = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget     = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber   = 1;
  Command.ModeRegisterDefinition = 0;

  
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

  
  HAL_Delay(100);

  
  Command.CommandMode       = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget       = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber   = 1;
  Command.ModeRegisterDefinition = 0;

  
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

  
  Command.CommandMode       = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget     = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber   = 4;
  Command.ModeRegisterDefinition = 0;

  
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

  
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget     = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber   = 1;
  Command.ModeRegisterDefinition = tmpmrd;

  
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

  
  
  
  HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);
}
