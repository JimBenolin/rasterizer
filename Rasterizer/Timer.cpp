#include "Timer.h"


CTimer::CTimer()
{
	QueryPerformanceFrequency(&mFrequency);
}


CTimer::~CTimer()
{
}
