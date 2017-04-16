#ifndef DATALOGGER_H
#define DATALOGGER_H

#include "buffer.h"

class DataLogger
{
public:
    DataLogger(Buffer *buffer, int channel);

    int runDataLogger();
    int initDataLogger();
    int channel;
    int drdy_GPIO;
    int valuearray[100];
    int average;
    int sum;
    Buffer *buffer;
};

#endif // DATALOGGER_H
