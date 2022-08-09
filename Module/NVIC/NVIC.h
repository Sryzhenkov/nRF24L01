#ifndef __NVIC_H
#define __NVIC_H

#include "GlobalSettings.h"

void NVIC_Init(void);
extern void EXTI15_10_IRQHandler(void);

#endif /* __NVIC_H */
