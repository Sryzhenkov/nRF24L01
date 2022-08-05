#include "Uart.h"

char sBuff[4096] = {0};

/*
		RX -- PA10
		TX -- PA9
*/

void uartInit(void)
{
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
		GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
		GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
		
		//TX
		GPIOA->CRH |= (GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1);
		//RX
		GPIOA->CRH |= GPIO_CRH_CNF10_1;
		GPIOA->BSRR |= GPIO_ODR_ODR10;
	
//USARTDIV = Fck / (16 * BAUD) = 72000000 / (16 * 9600) = 468,75
//USART_BRR = 468,75 * 16 = 7500.
	
//   	USART1->BRR = 625;						// 115200		//72MHz
//  USART1->BRR = 416;						// 115200		//48MHz
	
		USART1->BRR	= BD_UART(72000000,115200);
	
		USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
		USART1->CR2 = 0;
		USART1->CR3 = 0;
	
		USART1->CR1 |= USART_CR1_UE; 
		
//		NVIC_EnableIRQ(USART1_IRQn);
}

void Send (char* Array){

	while(*Array)
	{
		while(!(USART1->SR & USART_SR_TC));

		USART1->DR = *Array;
		Array++;
	}
}
