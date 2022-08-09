#include "GlobalSettings.h"

const static char* const globalState[]	= {"Disconnected", "Connected"};

#ifdef NRF_TX_MODE
static uint8_t inc = 0;
#endif

t_SystemInfo sSystemInfo = {
																.status = 0,
};

int main()
{
	//__enable_irq ();
	
	System_Init_72MHZ(); //note: Change system_stm32f10x.c file 
	SysTick_Init();
	NVIC_Init();
  PC13_LED_INIT
	uartInit();
	spiInit();
	
	SEND("START APPLICATION\r\n%s\r\n",SW_VERSION)
	
	//TODO: later
	sSystemInfo.status = CheckNRF24();		
	
	SEND("[NRF] Status: %s\r\n", globalState[sSystemInfo.status])
	
	if(sSystemInfo.status)
	 {
			InitNRF24(&sNRFInfo);
			ReadAllReg(); 
		}
	else
		{
			SEND("[NRF] Please connect the module and reboot this device\r\n")
			return 0;
		}
	
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
