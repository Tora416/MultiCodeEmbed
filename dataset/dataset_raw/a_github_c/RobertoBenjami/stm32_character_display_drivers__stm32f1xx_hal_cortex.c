


#include "stm32f1xx_hal.h"





#ifdef HAL_CORTEX_MODULE_ENABLED















void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
  
  
  NVIC_SetPriorityGrouping(PriorityGroup);
}


void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{ 
  uint32_t prioritygroup = 0x00U;
  
  
  assert_param(IS_NVIC_SUB_PRIORITY(SubPriority));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));
  
  prioritygroup = NVIC_GetPriorityGrouping();
  
  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}


void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
  
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  
  NVIC_EnableIRQ(IRQn);
}


void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
  
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  
  NVIC_DisableIRQ(IRQn);
}


void HAL_NVIC_SystemReset(void)
{
  
  NVIC_SystemReset();
}


uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb)
{
   return SysTick_Config(TicksNumb);
}




#if (__MPU_PRESENT == 1U)

void HAL_MPU_Disable(void)
{
  
  __DMB();

  
  SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
  
  
  MPU->CTRL = 0U;
}


void HAL_MPU_Enable(uint32_t MPU_Control)
{
  
  MPU->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;
  
  
  SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
  
  
  __DSB();
  __ISB();
}


void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_Init)
{
  
  assert_param(IS_MPU_REGION_NUMBER(MPU_Init->Number));
  assert_param(IS_MPU_REGION_ENABLE(MPU_Init->Enable));

  
  MPU->RNR = MPU_Init->Number;

  if ((MPU_Init->Enable) != RESET)
  {
    
    assert_param(IS_MPU_INSTRUCTION_ACCESS(MPU_Init->DisableExec));
    assert_param(IS_MPU_REGION_PERMISSION_ATTRIBUTE(MPU_Init->AccessPermission));
    assert_param(IS_MPU_TEX_LEVEL(MPU_Init->TypeExtField));
    assert_param(IS_MPU_ACCESS_SHAREABLE(MPU_Init->IsShareable));
    assert_param(IS_MPU_ACCESS_CACHEABLE(MPU_Init->IsCacheable));
    assert_param(IS_MPU_ACCESS_BUFFERABLE(MPU_Init->IsBufferable));
    assert_param(IS_MPU_SUB_REGION_DISABLE(MPU_Init->SubRegionDisable));
    assert_param(IS_MPU_REGION_SIZE(MPU_Init->Size));
    
    MPU->RBAR = MPU_Init->BaseAddress;
    MPU->RASR = ((uint32_t)MPU_Init->DisableExec             << MPU_RASR_XN_Pos)   |
                ((uint32_t)MPU_Init->AccessPermission        << MPU_RASR_AP_Pos)   |
                ((uint32_t)MPU_Init->TypeExtField            << MPU_RASR_TEX_Pos)  |
                ((uint32_t)MPU_Init->IsShareable             << MPU_RASR_S_Pos)    |
                ((uint32_t)MPU_Init->IsCacheable             << MPU_RASR_C_Pos)    |
                ((uint32_t)MPU_Init->IsBufferable            << MPU_RASR_B_Pos)    |
                ((uint32_t)MPU_Init->SubRegionDisable        << MPU_RASR_SRD_Pos)  |
                ((uint32_t)MPU_Init->Size                    << MPU_RASR_SIZE_Pos) |
                ((uint32_t)MPU_Init->Enable                  << MPU_RASR_ENABLE_Pos);
  }
  else
  {
    MPU->RBAR = 0x00U;
    MPU->RASR = 0x00U;
  }
}
#endif 


uint32_t HAL_NVIC_GetPriorityGrouping(void)
{
  
  return NVIC_GetPriorityGrouping();
}


void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority)
{
  
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
 
  NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, pPreemptPriority, pSubPriority);
}


void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
  
  NVIC_SetPendingIRQ(IRQn);
}


uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  
  return NVIC_GetPendingIRQ(IRQn);
}


void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  
  NVIC_ClearPendingIRQ(IRQn);
}


uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn)
{
  
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  
  return NVIC_GetActive(IRQn);
}


void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
{
  
  assert_param(IS_SYSTICK_CLK_SOURCE(CLKSource));
  if (CLKSource == SYSTICK_CLKSOURCE_HCLK)
  {
    SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
  }
  else
  {
    SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
  }
}


void HAL_SYSTICK_IRQHandler(void)
{
  HAL_SYSTICK_Callback();
}


__weak void HAL_SYSTICK_Callback(void)
{
  
}





#endif 





