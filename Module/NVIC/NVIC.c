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
static uint8_t r = 0;
#endif

void EXTI15_10_IRQHandler(void)
{
	t_nrfInfo* pNRFInfo = &sNRFInfo;
	uint8_t 	 clearStatus	= 0x70;
	
	EXTI->PR |= EXTI_PR_PR12;	

	PC13_CHANGE	
	
#ifdef NRF_RX_MODE
	ReadNRF24(CMD_R_RX_PAYLOAD,&r,1);	
	pNRFInfo->status = ReadNRF24(REG_RPD,&(pNRFInfo->RPD),1);
	SEND("[NRF] Read....%u\r\n[NRF] S: %x | RPD: %x\r\n", r,pNRFInfo->status,pNRFInfo->RPD)	//if RP(Received Power) > -64dBm ---> RPD = 1 // else RP < -64dBm ---> RPD = 0 
#endif
	
#ifdef NRF_TX_MODE
	pNRFInfo->status = ReadNRF24(REG_OBSERVE_TX,&(pNRFInfo->obsTX),1);
	SEND("[NRF] S: %x | OBS: %x\r\n", pNRFInfo->status, pNRFInfo->obsTX)
#endif
	
	WriteNRF24(REG_STATUS,&clearStatus,1);
	
	SEND("OK\r\n")
}
