 


#include "stm32f4xx_hal.h"





#ifdef HAL_PWR_MODULE_ENABLED



    
#define PWR_OVERDRIVE_TIMEOUT_VALUE  1000U
#define PWR_UDERDRIVE_TIMEOUT_VALUE  1000U
#define PWR_BKPREG_TIMEOUT_VALUE     1000U
#define PWR_VOSRDY_TIMEOUT_VALUE     1000U


   









HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void)
{
  uint32_t tickstart = 0U;

  *(__IO uint32_t *) CSR_BRE_BB = (uint32_t)ENABLE;

  
  tickstart = HAL_GetTick();

    
  while(__HAL_PWR_GET_FLAG(PWR_FLAG_BRR) == RESET)
  {
    if((HAL_GetTick() - tickstart ) > PWR_BKPREG_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    } 
  }
  return HAL_OK;
}


HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void)
{
  uint32_t tickstart = 0U;

  *(__IO uint32_t *) CSR_BRE_BB = (uint32_t)DISABLE;

  
  tickstart = HAL_GetTick();

    
  while(__HAL_PWR_GET_FLAG(PWR_FLAG_BRR) != RESET)
  {
    if((HAL_GetTick() - tickstart ) > PWR_BKPREG_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    } 
  }
  return HAL_OK;
}


void HAL_PWREx_EnableFlashPowerDown(void)
{
  *(__IO uint32_t *) CR_FPDS_BB = (uint32_t)ENABLE;
}


void HAL_PWREx_DisableFlashPowerDown(void)
{
  *(__IO uint32_t *) CR_FPDS_BB = (uint32_t)DISABLE;
}

  
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->CR & PWR_CR_VOS);
}

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx)

HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t tickstart = 0U;
  
  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));
  
  
  __HAL_RCC_PWR_CLK_ENABLE();
  
  
  __HAL_PWR_VOLTAGESCALING_CONFIG(VoltageScaling);
  
  
  tickstart = HAL_GetTick();
  while((__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY) == RESET))
  {
    if((HAL_GetTick() - tickstart ) > PWR_VOSRDY_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    } 
  }

  return HAL_OK;
}

#elif defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
      defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
      defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || \
      defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || \
      defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t tickstart = 0U;
  
  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));
  
  
  __HAL_RCC_PWR_CLK_ENABLE();
  
  
  if(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_PLL)
  {
    
    __HAL_RCC_PLL_DISABLE();
    
    
    tickstart = HAL_GetTick();    
      
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
    
    
    __HAL_PWR_VOLTAGESCALING_CONFIG(VoltageScaling);
    
    
    __HAL_RCC_PLL_ENABLE();
    
    
    tickstart = HAL_GetTick();
      
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      } 
    }
    
    
    tickstart = HAL_GetTick();
    while((__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY) == RESET))
    {
      if((HAL_GetTick() - tickstart ) > PWR_VOSRDY_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      } 
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
#endif 

#if defined(STM32F469xx) || defined(STM32F479xx)

void HAL_PWREx_EnableWakeUpPinPolarityRisingEdge(void)
{
  *(__IO uint32_t *) CSR_WUPP_BB = (uint32_t)DISABLE;
}


void HAL_PWREx_EnableWakeUpPinPolarityFallingEdge(void)
{
  *(__IO uint32_t *) CSR_WUPP_BB = (uint32_t)ENABLE;
}
#endif 

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) ||\
    defined(STM32F411xE) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
    defined(STM32F413xx) || defined(STM32F423xx)

void HAL_PWREx_EnableMainRegulatorLowVoltage(void)
{
  *(__IO uint32_t *) CR_MRLVDS_BB = (uint32_t)ENABLE;
}


void HAL_PWREx_DisableMainRegulatorLowVoltage(void)
{
  *(__IO uint32_t *) CR_MRLVDS_BB = (uint32_t)DISABLE;
}


void HAL_PWREx_EnableLowRegulatorLowVoltage(void)
{
  *(__IO uint32_t *) CR_LPLVDS_BB = (uint32_t)ENABLE;
}


void HAL_PWREx_DisableLowRegulatorLowVoltage(void)
{
  *(__IO uint32_t *) CR_LPLVDS_BB = (uint32_t)DISABLE;
}

#endif 

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

HAL_StatusTypeDef HAL_PWREx_EnableOverDrive(void)
{
  uint32_t tickstart = 0U;

  __HAL_RCC_PWR_CLK_ENABLE();
  
  
  __HAL_PWR_OVERDRIVE_ENABLE();

  
  tickstart = HAL_GetTick();

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_ODRDY))
  {
    if((HAL_GetTick() - tickstart) > PWR_OVERDRIVE_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }
  
  
  __HAL_PWR_OVERDRIVESWITCHING_ENABLE();

  
  tickstart = HAL_GetTick();

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_ODSWRDY))
  {
    if((HAL_GetTick() - tickstart ) > PWR_OVERDRIVE_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  } 
  return HAL_OK;
}


HAL_StatusTypeDef HAL_PWREx_DisableOverDrive(void)
{
  uint32_t tickstart = 0U;
  
  __HAL_RCC_PWR_CLK_ENABLE();
    
  
  __HAL_PWR_OVERDRIVESWITCHING_DISABLE();
  
  
  tickstart = HAL_GetTick();
 
  while(__HAL_PWR_GET_FLAG(PWR_FLAG_ODSWRDY))
  {
    if((HAL_GetTick() - tickstart) > PWR_OVERDRIVE_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  } 
  
  
  __HAL_PWR_OVERDRIVE_DISABLE();

  
  tickstart = HAL_GetTick();

  while(__HAL_PWR_GET_FLAG(PWR_FLAG_ODRDY))
  {
    if((HAL_GetTick() - tickstart) > PWR_OVERDRIVE_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }
  
  return HAL_OK;
}


HAL_StatusTypeDef HAL_PWREx_EnterUnderDriveSTOPMode(uint32_t Regulator, uint8_t STOPEntry)
{
  uint32_t tmpreg1 = 0U;

  
  assert_param(IS_PWR_REGULATOR_UNDERDRIVE(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));
  
  
  __HAL_RCC_PWR_CLK_ENABLE();
  
  
  __HAL_PWR_CLEAR_ODRUDR_FLAG();
  
   
  __HAL_PWR_UNDERDRIVE_ENABLE();

  
  tmpreg1 = PWR->CR;
  
  tmpreg1 &= (uint32_t)~(PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_LPUDS | PWR_CR_MRUDS);
  
  
  tmpreg1 |= Regulator;
  
  
  PWR->CR = tmpreg1;
  
  
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
  
  if(STOPEntry == PWR_SLEEPENTRY_WFI)
  {   
    
    __WFI();
  }
  else
  {
    
    __WFE();
  }
  
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

  return HAL_OK;  
}

#endif 




#endif 





