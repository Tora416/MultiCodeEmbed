



  
  


#include "stm32f1xx.h"









#if !defined  (HSE_VALUE) 
  #define HSE_VALUE               8000000U 
#endif 

#if !defined  (HSI_VALUE)
  #define HSI_VALUE               8000000U 
#endif 

 
#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)

#endif 

 

#define VECT_TAB_OFFSET  0x00000000U 











#if defined(STM32F100xB) ||defined(STM32F100xE)
  uint32_t SystemCoreClock         = 24000000U;        
#else 
  uint32_t SystemCoreClock         = 72000000U;        
#endif

const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8U] =  {0, 0, 0, 0, 1, 2, 3, 4};





#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
#ifdef DATA_IN_ExtSRAM
  static void SystemInit_ExtMemCtl(void); 
#endif 
#endif 






void SystemInit (void)
{
  
  
  RCC->CR |= 0x00000001U;

  
#if !defined(STM32F105xC) && !defined(STM32F107xC)
  RCC->CFGR &= 0xF8FF0000U;
#else
  RCC->CFGR &= 0xF0FF0000U;
#endif    
  
  
  RCC->CR &= 0xFEF6FFFFU;

  
  RCC->CR &= 0xFFFBFFFFU;

  
  RCC->CFGR &= 0xFF80FFFFU;

#if defined(STM32F105xC) || defined(STM32F107xC)
  
  RCC->CR &= 0xEBFFFFFFU;

  
  RCC->CIR = 0x00FF0000U;

  
  RCC->CFGR2 = 0x00000000U;
#elif defined(STM32F100xB) || defined(STM32F100xE)
  
  RCC->CIR = 0x009F0000U;

  
  RCC->CFGR2 = 0x00000000U;      
#else
  
  RCC->CIR = 0x009F0000U;
#endif 
    
#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
  #ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl(); 
  #endif 
#endif 

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; 
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
#endif 
}


void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0U, pllmull = 0U, pllsource = 0U;

#if defined(STM32F105xC) || defined(STM32F107xC)
  uint32_t prediv1source = 0U, prediv1factor = 0U, prediv2factor = 0U, pll2mull = 0U;
#endif 

#if defined(STM32F100xB) || defined(STM32F100xE)
  uint32_t prediv1factor = 0U;
#endif 
    
  
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00U:  
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x04U:  
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x08U:  

      
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      
#if !defined(STM32F105xC) && !defined(STM32F107xC)      
      pllmull = ( pllmull >> 18U) + 2U;
      
      if (pllsource == 0x00U)
      {
        
        SystemCoreClock = (HSI_VALUE >> 1U) * pllmull;
      }
      else
      {
 #if defined(STM32F100xB) || defined(STM32F100xE)
       prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1U;
       
       SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull; 
 #else
        
        if ((RCC->CFGR & RCC_CFGR_PLLXTPRE) != (uint32_t)RESET)
        {
          SystemCoreClock = (HSE_VALUE >> 1U) * pllmull;
        }
        else
        {
          SystemCoreClock = HSE_VALUE * pllmull;
        }
 #endif
      }
#else
      pllmull = pllmull >> 18U;
      
      if (pllmull != 0x0DU)
      {
         pllmull += 2U;
      }
      else
      { 
        pllmull = 13U / 2U; 
      }
            
      if (pllsource == 0x00U)
      {
        
        SystemCoreClock = (HSI_VALUE >> 1U) * pllmull;
      }
      else
      {
        
        
        prediv1source = RCC->CFGR2 & RCC_CFGR2_PREDIV1SRC;
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1U;
        
        if (prediv1source == 0U)
        { 
          
          SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull;          
        }
        else
        {
          
          
          prediv2factor = ((RCC->CFGR2 & RCC_CFGR2_PREDIV2) >> 4U) + 1U;
          pll2mull = ((RCC->CFGR2 & RCC_CFGR2_PLL2MUL) >> 8U) + 2U; 
          SystemCoreClock = (((HSE_VALUE / prediv2factor) * pll2mull) / prediv1factor) * pllmull;                         
        }
      }
#endif  
      break;

    default:
      SystemCoreClock = HSI_VALUE;
      break;
  }
  
  
  
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4U)];
  
  SystemCoreClock >>= tmp;  
}

#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
 
#ifdef DATA_IN_ExtSRAM
 
void SystemInit_ExtMemCtl(void) 
{
  __IO uint32_t tmpreg;
  

  
  RCC->AHBENR = 0x00000114U;

  
  tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_FSMCEN);
  
  
  RCC->APB2ENR = 0x000001E0U;
  
  
  tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPDEN);

  (void)(tmpreg);
  


  


  
  GPIOD->CRL = 0x44BB44BBU;  
  GPIOD->CRH = 0xBBBBBBBBU;

  GPIOE->CRL = 0xB44444BBU;  
  GPIOE->CRH = 0xBBBBBBBBU;

  GPIOF->CRL = 0x44BBBBBBU;  
  GPIOF->CRH = 0xBBBB4444U;

  GPIOG->CRL = 0x44BBBBBBU;  
  GPIOG->CRH = 0x444B4B44U;
   
  

  
  FSMC_Bank1->BTCR[4U] = 0x00001091U;
  FSMC_Bank1->BTCR[5U] = 0x00110212U;
}
#endif 
#endif 




  
    

