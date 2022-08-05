#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

typedef struct
{
	   uint32_t holdup;
	   uint32_t count;
	   uint32_t active;
	   uint32_t flag;
}sTimer_s;

extern sTimer_s sTimer[1];

void sTimerStart(uint8_t Start, uint32_t Holdup);

#endif /* __TIMER_H */
