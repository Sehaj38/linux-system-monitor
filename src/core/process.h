#ifndef PROCESS_H
#define PROCESS_H

struct ProcessInfo {
    int running;
    int total;
};

ProcessInfo getProcessInfo();

#endif
