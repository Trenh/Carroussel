#pragma once
#include <bx/timer.h>

class Timer {
public:
	static int64_t	timeOffset;
	
	static float getTime() { return (float)((bx::getHPCounter() - Timer::timeOffset) / double(bx::getHPFrequency())); }
};