#include<iostream>
#include<unistd.h>
#include "cpu.h"
using namespace std;

int main() {
    CPUData prev = readCPU();
    while(true) {
        sleep(1);
        CPUData curr = readCPU();
        double CPUUsage = calculateCPU(prev, curr);

        cout << "\rCPU Usage : " << CPUUsage << "%   " << flush;

        prev = curr;
    }
    return 0;
}