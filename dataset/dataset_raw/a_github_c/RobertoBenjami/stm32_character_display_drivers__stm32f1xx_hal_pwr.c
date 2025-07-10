


#include "stm32f1xx_hal.h"





#ifdef HAL_PWR_MODULE_ENABLED





  
 
#define PVD_MODE_IT               0x00010000U
#define PVD_MODE_EVT              0x00020000U
#define PVD_RISING_EDGE           0x00000001U
#define PVD_FALLING_EDGE          0x00000002U



 

#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)
#define PWR_CR_OFFSET            0x00U
#define PWR_CSR_OFFSET           0x04U
#define PWR_CR_OFFSET_BB         (PWR_OFFSET + PWR_CR_OFFSET)
#define PWR_CSR_OFFSET_BB        (PWR_OFFSET + PWR_CSR_OFFSET)

   
  


#define LPSDSR_BIT_NUMBER        PWR_CR_LPDS_Pos
#define CR_LPSDSR_BB             ((uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (LPSDSR_BIT_NUMBER * 4U)))


#define DBP_BIT_NUMBER            PWR_CR_DBP_Pos
#define CR_DBP_BB                ((uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (DBP_BIT_NUMBER * 4U)))


#define PVDE_BIT_NUMBER           PWR_CR_PVDE_Pos
#define CR_PVDE_BB               ((uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (PVDE_BIT_NUMBER * 4U)))







#define CSR_EWUP_BB(VAL)         ((uint32_t)(PERIPH_BB_BASE + (PWR_CSR_OFFSET_BB * 32U) + (POSITION_VAL(VAL) * 4U)))

  





static void PWR_OverloadWfe(void);


__NOINLINE
static void PWR_OverloadWfe(void)
{
  __asm volatile( "wfe" );
  __asm volatile( "nop" );
}









void HAL_PWR_DeInit(void)
{
  __HAL_RCC_PWR_FORCE_RESET();
  __HAL_RCC_PWR_RELEASE_RESET();
}


void HAL_PWR_EnableBkUpAccess(void)
{
  
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)ENABLE;
}


void HAL_PWR_DisableBkUpAccess(void)
{
  
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)DISABLE;
}






void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD)
{
  
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  
  MODIFY_REG(PWR->CR, PWR_CR_PLS, sConfigPVD->PVDLevel);
  
  
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE(); 
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();

  
  if((sConfigPVD->Mode & PVD_MODE_IT) == PVD_MODE_IT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }
  
  
  if((sConfigPVD->Mode & PVD_MODE_EVT) == PVD_MODE_EVT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_EVENT();
  }
  
  
  if((sConfigPVD->Mode & PVD_RISING_EDGE) == PVD_RISING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }
  
  if((sConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
  }
}


void HAL_PWR_EnablePVD(void)
{
  
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)ENABLE;
}


void HAL_PWR_DisablePVD(void)
{
  
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)DISABLE;
}


void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx)
{
  
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));
  
  *(__IO uint32_t *) CSR_EWUP_BB(WakeUpPinx) = (uint32_t)ENABLE;
}


void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx)
{
  
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));
  
  *(__IO uint32_t *) CSR_EWUP_BB(WakeUpPinx) = (uint32_t)DISABLE;
}


void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry)
{
  
  
  
  UNUSED(Regulator);

  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  
  if(SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    
    __WFI();
  }
  else
  {
    
    __SEV();
    __WFE();
    __WFE();
  }
}


void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry)
{
  
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

   
  CLEAR_BIT(PWR->CR,  PWR_CR_PDDS);

  
  MODIFY_REG(PWR->CR, PWR_CR_LPDS, Regulator);

  
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  
  if(STOPEntry == PWR_STOPENTRY_WFI)
  {
    
    __WFI();
  }
  else
  {
    
    __SEV();
    PWR_OverloadWfe(); 
    PWR_OverloadWfe(); 
  }
  
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}


void HAL_PWR_EnterSTANDBYMode(void)
{
  
  SET_BIT(PWR->CR, PWR_CR_PDDS);

  
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  
#if defined ( __CC_ARM)
  __force_stores();
#endif
  
  __WFI();
}



void HAL_PWR_EnableSleepOnExit(void)
{
  
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}



void HAL_PWR_DisableSleepOnExit(void)
{
  
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}



void HAL_PWR_EnableSEVOnPend(void)
{
  
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}



void HAL_PWR_DisableSEVOnPend(void)
{
  
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}




void HAL_PWR_PVD_IRQHandler(void)
{
  
  if(__HAL_PWR_PVD_EXTI_GET_FLAG() != RESET)
  {
    
    HAL_PWR_PVDCallback();

    
    __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
  }
}


__weak void HAL_PWR_PVDCallback(void)
{
   
}





#endif 





