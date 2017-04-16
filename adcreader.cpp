#include "adcreader.h"
#include <QDebug>

#include "datalogger.h"

//Constructor
ADCreader::ADCreader(Buffer *buffer, int channel){
    this->running=false;
    this->channel = channel;
    this->buffer = buffer;
    currentValue = new int();
}
//Deconstructor
ADCreader::~ADCreader(){
}


void ADCreader::run()
{
    DataLogger logger(this->buffer, this->channel);

    logger.runDataLogger();
}




void ADCreader::quit()
{
    running = false;
    exit(0);
}


