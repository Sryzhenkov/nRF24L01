#ifndef _SYSTICK_LM3S_
#define _SYSTICK_LM3S_

#include "stm32f10x.h"
#include "Timer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern volatile  uint32_t  sys_timecount;
extern           void      SysTick_Handler(void);
extern           void      SysTick_Init(void);
extern           void      delay(uint32_t);

#endif
