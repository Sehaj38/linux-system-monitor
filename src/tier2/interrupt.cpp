#include "interrupt.h"
#include <fstream>

long long readInterrupts()
{
    std::ifstream f("/proc/stat");
    std::string key;
    long long val;

    while (f >> key >> val)
        if (key == "intr")
            return val;

    return 0;
}
