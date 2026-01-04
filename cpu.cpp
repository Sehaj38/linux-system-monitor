#include "cpu.h"
#include<fstream>
#include<string>
using namespace std;

CPUData readCPU() {
    ifstream file("/proc/stat");
    string cpu;
    long long value;
    long long idle = 0, total = 0;

    file >> cpu;

    for(int i = 0; i < 10; i++){ // 10 fields read
        file >> value;
        total += value;

        if( i == 3 || i == 4){ // time[3] and time[4]  -> idle + iowait time
            idle += value;
        }
    }
    return {idle, total};
}
double calculateCPU(const CPUData &prev, const CPUData &curr){
    long long deltaIdle = curr.idle - prev.idle;
    long long deltaTotal = curr.total - prev.total;

    if(deltaTotal == 0){
        return 0.0;
    }

    return (double) (deltaTotal - deltaIdle) / deltaTotal * 100.0; // returns cpu usage
}