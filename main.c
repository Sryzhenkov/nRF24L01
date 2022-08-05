#include "stm32f10x.h"
#include "System.h"
#include "Led.h"
#include "Uart.h"
#include "spi.h"
#include "nRF24.h"
#include "SysTick.h"
#include "Timer.h"
#include "NVIC.h"

#define VERSION_SW 			"v.0.0.1"

#ifdef NRF_TX_MODE
static uint8_t inc = 0;
#endif

int main()
{
	//__enable_irq ();
	
	System_Init_72MHZ(); //note: Change system_stm32f10x.c file 
	SysTick_Init();
	NVIC_Init();
  PC13_LED_INIT
	uartInit();
	spiInit();
	
	SEND("START APPLICATION\r\n%s\r\n",VERSION_SW)
	SEND("[NRF] Status: %s\r\n", CheckNRF24())
	
	InitNRF24(&sNRFInfo);
	ReadAllReg();
	
	delay(10000);
#ifdef NRF_RX_MODE
	CE_HIGH
#endif
	while(1)
		{
#ifdef NRF_TX_MODE
			
  		WriteNRF24(CMD_W_TX_PAYLOAD,&inc,1);
			
			CE_HIGH
			delay(1);
			CE_LOW
			
			SEND("[NRF] Send....\r\n")
			
			inc++;
			
#endif
			delay(1000);
		}
}
