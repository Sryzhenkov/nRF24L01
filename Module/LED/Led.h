#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define PC13_LED_INIT	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 			\
			GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);	\
			GPIOC->CRH |= GPIO_CRH_MODE13_1;			\
			GPIOC->ODR |= GPIO_ODR_ODR13; 

#define PC13_LED(M)	if(M == 0) GPIOC->ODR |= GPIO_ODR_ODR13; \
										else 			 GPIOC->ODR &= (uint16_t)~GPIO_ODR_ODR13;

#define PC13_CHANGE	GPIOC->ODR ^= GPIO_ODR_ODR13; 

#endif /* __LED_H */
