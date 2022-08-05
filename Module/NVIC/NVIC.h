#ifndef __NVIC_H
#define __NVIC_H

#include "stm32f10x.h"
#include "spi.h"
#include "nRF24.h"

void NVIC_Init(void);
extern void EXTI15_10_IRQHandler(void);

#endif /* __NVIC_H */
