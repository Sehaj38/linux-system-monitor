#ifndef DISK_H
#define DISK_H

struct DiskIO {
    long long readKB;
    long long writeKB;
};

DiskIO readDisk();
DiskIO calcDiskRate(const DiskIO&, const DiskIO&);

#endif
