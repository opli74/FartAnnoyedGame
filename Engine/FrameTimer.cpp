#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer() : last(std::chrono::high_resolution_clock::now()) {}

float FrameTimer::Mark()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<float>(now - last);
    last = now;

    return duration.count();
}


