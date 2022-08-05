#include "Timer.h"

sTimer_s sTimer[1] = {0};

void sTimerStart(uint8_t Start, uint32_t Holdup)
{
	sTimer[0].holdup = Holdup;
	sTimer[0].flag = 0;
	sTimer[0].active = Start;
}
