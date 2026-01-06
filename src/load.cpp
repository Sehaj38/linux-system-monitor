#include "load.h"
#include<fstream>
using namespace std;

LoadAvg getLoadAverage() {
    ifstream file("/proc/loadavg");
    LoadAvg load{};
    file >> load.one >> load.five >> load.fifteen;
    return load;
}