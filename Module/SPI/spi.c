#include "spi.h"
	/*	SPI1
		NSS -- PA4
		SCK -- PA5
		MISO-- PA6
		MOSI-- PA7
	*/

void spiInit(void)
{
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	
		GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);																		//Congig CHIP ENABLE
		GPIOA->CRL |= GPIO_CRL_MODE3;																												//
		CE_LOW
	
		GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);																		//Congig CHIP SELECT
		GPIOA->CRL |= GPIO_CRL_MODE4;																												//
		CS_HIGH
	
		GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5 | GPIO_CRL_CNF6 | GPIO_CRL_MODE6 | GPIO_CRL_CNF7 | GPIO_CRL_MODE7);		//CONFIG MISO, MOSI, SCK
	
		//SCK
		GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_CNF5_1);																		//
		//MISO
		GPIOA->CRL |=  GPIO_CRL_CNF6_0;																											//
		//MOSI
		GPIOA->CRL |= (GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1);																		//
	
		SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_1 | SPI_CR1_MSTR);
		SPI1->CR1 |= SPI_CR1_SPE;
}
//TODO CHANGE MODE
void t_spiSend(uint8_t* data, uint32_t count, uint8_t mode)
{
	uint8_t r;

		do
		{
			PC13_CHANGE
			
			while(!(SPI1->SR & SPI_SR_TXE));
	
			if(mode == 1)
				SPI1->DR = *data;
			else
				SPI1->DR = *data++;
	
			while(!(SPI1->SR & SPI_SR_RXNE));
			
			if(mode == 1)
				*data++ = (uint8_t)SPI1->DR;
			else
				r = (uint8_t)SPI1->DR;
		
			count--;
		}while(count != 0);
	
}

void spiSend(uint8_t* data, uint32_t count, uint8_t mode)
{
	CS_LOW
	t_spiSend(data,count,mode);
	CS_HIGH
}
