#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
public:
    Buffer(int Value);
    Buffer();

    void test();
    void setCurrentValue(int channel, int curValue);
    int curValue_22;
    int counter_22;
    int values_22[100];

    float calculatesAvg(int channel);
};

#endif // BUFFER_H
