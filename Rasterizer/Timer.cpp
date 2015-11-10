#include "Timer.h"


CTimer::CTimer()
{
	QueryPerformanceFrequency(&mFrequency);
	set();
}


CTimer::~CTimer()
{
}
