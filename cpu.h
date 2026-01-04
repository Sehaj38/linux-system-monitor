#ifndef CPU_H
#define CPU_H

struct CPUData {
    long long idle;
    long long total;
};

CPUData readCPU();
double calculateCPU(const CPUData &prev, const CPUData &curr);

#endif