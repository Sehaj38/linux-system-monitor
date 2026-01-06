#include "mem.h"
#include <fstream>
#include <string>

double getMemoryUsage()
{
    std::ifstream file("/proc/meminfo");

    std::string key;
    long long value;
    std::string unit;

    long long memTotal = 0;
    long long memAvailable = 0;

    while (file >> key >> value >> unit)
    {
        if (key == "MemTotal:")
            memTotal = value;
        else if (key == "MemAvailable:")
            memAvailable = value;

        if (memTotal && memAvailable)
            break;
    }

    long long used = memTotal - memAvailable;
    return (double)used / memTotal * 100.0;
}
