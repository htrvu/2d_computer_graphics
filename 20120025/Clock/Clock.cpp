#include "Clock.h"

void Clock::start() {
    startOffset = high_resolution_clock::now();
}

void Clock::stop() {
    endOffset = high_resolution_clock::now(); 
}

double Clock::getTime() {
    duration<double> time = duration_cast<duration<double>>(endOffset - startOffset);
    return 1000.0 * time.count();
}