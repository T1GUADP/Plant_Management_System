#include <window.h>
#include <adcreader.h>
#include <QApplication>
#include <iostream>
#include <unistd.h>
#include "datalogger.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // create the window
    //Window window;
    //window.showFullScreen();

    // call the window.timerEvent function every 40 ms
   // window.startTimer(100);

    //WORK IN PROGRESS (START)
    //qDebug() << "Call new object of class ADCreader";
    ADCreader Thread1(1);
    Thread1.start();



    //for (int i=0; i< 30; i++) {
    //    qDebug() << "Main " << i;
    //    usleep(1000*1000);
    //}

    //Thread1.quit();

    //ADCreader.run(true);

    // execute the application
    //return 0;
    //WORK IN PROGRESS (END)
    return app.exec();
}
