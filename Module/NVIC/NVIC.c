#include "NVIC.h"

void NVIC_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;		//Enable PA and AFIO

	GPIOB->CRH &= ~(GPIO_CRH_CNF12 | GPIO_CRH_MODE12);				//Config IRQ PIN
	GPIOB->CRH |=  GPIO_CRH_CNF12_0;

	//GPIOB->ODR |= (1 << 1);
	AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PB;

	EXTI->FTSR |= EXTI_FTSR_TR12;

	EXTI->PR |= EXTI_PR_PR12;

	EXTI->IMR |= EXTI_IMR_MR12;

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

#ifdef NRF_RX_MODE
static uint16_t r = 0;
#endif

void EXTI15_10_IRQHandler(void)
{
	t_nrfInfo* pNRFInfo = &sNRFInfo;
	
	EXTI->PR |= EXTI_PR_PR12;	

	PC13_CHANGE	
	
#ifdef NRF_RX_MODE
	ReadNRF24(CMD_R_RX_PAYLOAD,(uint8_t*)&r,2);	
	SEND("[NRF] Read....%x %u\r\n", *((uint8_t*)&r),*(((uint8_t*)&r)+1))
#endif
	
	WriteNRF24(REG_STATUS,&(pNRFInfo->status),1);
	
	SEND("OK\r\n")
}
