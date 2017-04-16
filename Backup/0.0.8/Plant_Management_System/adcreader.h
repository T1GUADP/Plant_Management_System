#ifndef ADCREADER
#define ADCREADER

#include <QThread>
#include "buffer.h"

class ADCreader : public QThread
{
public:
    ADCreader(Buffer *buffer, int channel);    //constructor
    ~ADCreader(); //destructor
    int channel;
    int *currentValue;
    void quit();
    void run();
    Buffer *buffer;
private:
    bool running;

};

#endif
