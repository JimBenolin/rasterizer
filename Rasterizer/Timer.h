#pragma once

//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


class CTimer
{
private:
	LARGE_INTEGER mFrequency;
	LARGE_INTEGER mStart, mEnd, mElapsedMicroseconds;
public:
	CTimer();
	~CTimer();

	inline void set(void) { QueryPerformanceCounter(&mStart); }
	inline size_t get(void) {
		QueryPerformanceCounter(&mEnd);
		mElapsedMicroseconds.QuadPart = mEnd.QuadPart - mStart.QuadPart;
		mElapsedMicroseconds.QuadPart *= 1000000;
		mElapsedMicroseconds.QuadPart /= mFrequency.QuadPart;
		return mElapsedMicroseconds.QuadPart;
	}
};

