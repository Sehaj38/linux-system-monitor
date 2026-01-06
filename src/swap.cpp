#include "swap.h"
#include <fstream>
#include <string>

double getSwapUsage() {
    std::ifstream file("/proc/meminfo");
    std::string key, unit;
    long long value;
    long long total = 0, free = 0;

    while(file >> key >> value >> unit) {
        if(key == "SwapTotal:") total = value;
        else if(key == "SwapFree:") free = value;
        if(total && free) break;
    }
    if(total == 0) return 0.0;
    return (double)(total - free) / total * 100.0;
}
