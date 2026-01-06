#include "iowait.h"
#include <fstream>

IOWaitData readIOWait()
{
    std::ifstream f("/proc/stat");
    std::string cpu;
    long long v;
    long long total = 0, iowait = 0;

    f >> cpu;
    for (int i = 0; i < 10; i++) {
        f >> v;
        total += v;
        if (i == 4) iowait = v;
    }
    return { iowait, total };
}

double calculateIOWait(const IOWaitData& p, const IOWaitData& c)
{
    long long di = c.iowait - p.iowait;
    long long dt = c.total  - p.total;
    if (dt == 0) return 0;
    return (double)di / dt * 100.0;
}
