#ifndef GLOBALSETTINGS_H_
#define GLOBALSETTINGS_H_
//**********
#include "stdio.h"

#include "stm32f10x.h"

#include "System.h"
#include "Led.h"
#include "Uart.h"
#include "spi.h"
#include "nRF24.h"
#include "SysTick.h"
#include "Timer.h"
#include "NVIC.h"
//**********************************************************************
#define SW_VERSION					"v.0.0.3"

//#define NRF_TX_MODE
#define NRF_RX_MODE
//**********************************************************************
//**********************************************************************

//**********************************************************************
//**********************************************************************

//**********************************************************************


//**********************************************************************
//**********************************************************************
typedef struct{
								uint8_t status;
}t_SystemInfo;

extern t_SystemInfo sSystemInfo;

#endif /* GLOBALSETTINGS_H_ */
