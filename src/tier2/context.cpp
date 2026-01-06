#include "context.h"
#include <fstream>

long long readContextSwitches()
{
    std::ifstream f("/proc/stat");
    std::string key;
    long long val;

    while (f >> key >> val)
        if (key == "ctxt")
            return val;

    return 0;
}
