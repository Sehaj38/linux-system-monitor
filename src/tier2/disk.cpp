#include "disk.h"
#include <fstream>
#include <string>

DiskIO readDisk()
{
    std::ifstream f("/proc/diskstats");

    int ma, mi;
    std::string name;

    while (f >> ma >> mi >> name) {
        if (name == "nvme0n1") {
            long long readsCompleted;
            long long readsMerged;
            long long sectorsRead;
            long long timeReading;

            long long writesCompleted;
            long long writesMerged;
            long long sectorsWritten;
            long long timeWriting;

            f >> readsCompleted
              >> readsMerged
              >> sectorsRead
              >> timeReading
              >> writesCompleted
              >> writesMerged
              >> sectorsWritten
              >> timeWriting;

            return {
                sectorsRead / 2,
                sectorsWritten / 2
            };
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
