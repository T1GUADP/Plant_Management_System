#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
public:
    Buffer(int Value);
    Buffer();

    void test();
    void setCurrentValue(int channel, int curValue);
    int curValue_0;
    int counter_0;
    int values_0[100];
    int curValue_1;
    int counter_1;
    int values_1[100];

    float calculatesAvg(int channel);
};

#endif // BUFFER_H
