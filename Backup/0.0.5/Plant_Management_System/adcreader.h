#ifndef ADCREADER
#define ADCREADER

#include <QThread>

class ADCreader : public QThread
{
public:
    ADCreader(double frequency);    //constructor
    ~ADCreader(); //destructor
    void quit();
    void run();
private:
    bool running;

};

#endif
