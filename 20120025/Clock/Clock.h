#include <chrono>
using namespace std::chrono;

class Clock {
private:
    high_resolution_clock::time_point startOffset;
    high_resolution_clock::time_point endOffset;

public:
    void start();
    void stop();
    double getTime();
};