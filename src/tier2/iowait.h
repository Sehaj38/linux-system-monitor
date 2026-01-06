#ifndef IOWAIT_H
#define IOWAIT_H

struct IOWaitData {
    long long iowait;
    long long total;
};

IOWaitData readIOWait();
double calculateIOWait(const IOWaitData&, const IOWaitData&);

#endif
