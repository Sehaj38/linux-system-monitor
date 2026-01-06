#include "disk.h"
#include <fstream>
#include <string>

DiskIO readDisk()
{
    std::ifstream f("/proc/diskstats");
    int ma, mi;
    std::string name;
    long long rd, rds, wr, wrs;

    while (f >> ma >> mi >> name) {
        if (name == "nvme0n1") {
            f >> rd >> rds;
            f >> wr >> wrs;
            return { rds / 2, wrs / 2 }; // sectors → KB
        }
        f.ignore(1000, '\n');
    }
    return {0, 0};
}

DiskIO calcDiskRate(const DiskIO& p, const DiskIO& c)
{
    return {
        c.readKB  - p.readKB,
        c.writeKB - p.writeKB
    };
}
