#ifndef __SPI_H
#define __SPI_H

#include "GlobalSettings.h"

#define		 CE_LOW 	GPIOA->ODR &= (uint16_t)~GPIO_ODR_ODR3;
#define 	 CE_HIGH 	GPIOA->ODR |= GPIO_ODR_ODR3;

#define		 CS_LOW 	GPIOA->ODR &= (uint16_t)~GPIO_ODR_ODR4;
#define 	 CS_HIGH 	GPIOA->ODR |= GPIO_ODR_ODR4;

#define READ_MODE		1	
#define WRITE_MODE	0

void spiInit(void);

void t_spiSend(uint8_t* data, uint32_t count, uint8_t mode);
void spiSend(uint8_t* data, uint32_t count, uint8_t mode);

#endif /* __SPI_H */
