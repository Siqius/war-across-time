#include "Time.h"
#include <chrono>
using namespace std::chrono;

long Time::get_time() {
    auto now = system_clock::now();
    auto millis = duration_cast<milliseconds>(now.time_since_epoch()).count();
    return millis;
}