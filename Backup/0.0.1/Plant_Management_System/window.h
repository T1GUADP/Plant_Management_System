#ifndef WINDOW_H
#define WINDOW_H
#include <QtCore>

class window : public QThread
{
public:
    window();
    void run();
};

#endif // WINDOW_H
