#ifndef LOAD_H
#define LOAD_H

struct LoadAvg {
    double one;
    double five;
    double fifteen;
};

LoadAvg getLoadAverage();

#endif