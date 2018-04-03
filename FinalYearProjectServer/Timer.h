#pragma once
#include <chrono>

class Timer
{
public:
	void StartTimer();
	void SnapShotTimer();
	int GetTimerTimeInMilliseconds();

private:
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::high_resolution_clock::time_point TimePoint;
	typedef std::chrono::duration<float> Duration;
	typedef std::chrono::milliseconds Ms;

	TimePoint endTime;
	TimePoint startTime;
};

