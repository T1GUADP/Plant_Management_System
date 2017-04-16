#include <window.h>
#include <adcreader.h>
#include <QApplication>
#include <iostream>
#include <unistd.h>
#include "datalogger.h"
#include <buffer.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    //create the Data buffer
    Buffer *buffer;
    buffer = new Buffer();



     //create the window
    Window window (buffer);
    window.showMaximized();

    // call the window.timerEvent function every 40 ms
    window.startTimer(100);


    return app.exec();
}
