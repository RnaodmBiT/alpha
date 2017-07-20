#pragma once

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

class Stopwatch {
public:
    Stopwatch() {
        Reset();
    }

    float Reset() {
        float t = Time();
        start = Clock::now();
        return t;
    }

    float Time() const {
        Clock::time_point now = Clock::now();
        std::chrono::duration<float> span = std::chrono::duration_cast<std::chrono::duration<float>>(now - start);
        return span.count();
    }

private:
    Clock::time_point start;
};

