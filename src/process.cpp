#include "process.h"
#include <fstream>
#include <string>
using namespace std;

ProcessInfo getProcessInfo() {
    ifstream file("/proc/stat");
    string line;
    ProcessInfo info{0,0};

    while(getline(file, line)) {
        if(line.find("procs_running") == 0)
            info.running = stoi(line.substr(14));
        else if(line.find("processes") == 0)
            info.total = stoi(line.substr(10));
    }
    return info;
}
