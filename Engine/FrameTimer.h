#pragma once
#include <chrono>
#include <vector>
class FrameTimer
{
public:
	FrameTimer();
	float Mark();
private:
	std::chrono::steady_clock::time_point last;
};