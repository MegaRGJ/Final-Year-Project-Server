#include "stdafx.h"
#include "Timer.h"

void Timer::StartTimer()
{
	startTime = Clock::now();
}

void Timer::SnapShotTimer()
{
	endTime = Clock::now();
}

int Timer::GetTimerTimeInMilliseconds()
{
	Duration time = endTime - startTime;
	Ms msTime = std::chrono::duration_cast<Ms>(time);

	return msTime.count();

}
