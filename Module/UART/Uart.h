#ifndef __UART_H
#define __UART_H

#include "GlobalSettings.h"

extern char sBuff[4096];

#define BD_UART(FCK,BD)		( FCK / (16 * BD) ) * 16
#define SEND(FORMAT,...)		sprintf(sBuff,FORMAT,##__VA_ARGS__);Send(sBuff);

void uartInit(void);
void Send(char* Array);

#endif /* __UART_H */
