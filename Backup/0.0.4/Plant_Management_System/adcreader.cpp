#include "adcreader.h"
#include <QDebug>

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
    this->running = true;
    while (running) {
        qDebug() << "Tick";
        sleep(1);
    }
}

void ADCreader::quit()
{
    running = false;
    exit(0);
}


