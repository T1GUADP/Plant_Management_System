#include "adcreader.h"
#include <QDebug>

#include "datalogger.h"

//Constructor
ADCreader::ADCreader(double frequency){
    this->running=false;
    qDebug() << "frequency: " << frequency;
}
//Deconstructor
ADCreader::~ADCreader(){
}


void ADCreader::run()
{
    DataLogger logger;
   logger.initDataLogger();
    this->running = true;

    int tmpValues[100];
    for (int i=0; i< 100; i++) tmpValues[i] = 0;
    int counter = 0;
    while (running) {
        int curValue = logger.runDataLogger();
        tmpValues[counter] = curValue;

        float movAvg = 0.;

        for (int i=0; i < 100; i++) movAvg += tmpValues[i];
        movAvg = movAvg / 100;

        qDebug() << "Average value; " << movAvg;
        if (counter = 99) counter = 0;
        else counter ++;
        sleep(1);
    }
}

void ADCreader::quit()
{
    running = false;
    exit(0);
}


