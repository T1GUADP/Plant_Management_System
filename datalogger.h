#ifndef DATALOGGER_H
#define DATALOGGER_H

class DataLogger
{
public:
    DataLogger();

    int runDataLogger();
    int initDataLogger();
    int fd;
    int sysfs_fd;
    int no_tty;
    int ret;
};

#endif // DATALOGGER_H
