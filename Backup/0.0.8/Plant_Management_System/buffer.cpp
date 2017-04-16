#include "buffer.h"
#include <iostream>

using namespace std;

Buffer::Buffer()
{
    cout << "Buffer created" << endl;
    this->curValue_0 = 0;
    for (int i=0; i < 100; i++ ){
        this->values_0[i] = 0;
        this->counter_0 = 0;
    }
    for (int i=0; i < 100; i++ ){
        this->values_1[i] = 0;
        this->counter_1 = 0;
    }
}

void Buffer::test(){
    cout << "Test function is running" << endl;
}
//Buffer for channel 1 & 2
void Buffer::setCurrentValue(int channel, int curValue) {
    if (channel == 0) {
        this->curValue_0 = curValue;
        //write  into array
        this->values_0[this->counter_0] = this->curValue_0;
        //cout << "Counter: " << this->counter_0 << "   |   " << curValue << " == " << curValue_0 <<"==" << values_0[this->counter_0] << endl;
        if (this->counter_0 == 99) this->counter_0 = 0;
        else this->counter_0++;
        //restart array target
    } else if (channel == 1) {
        this->curValue_1 = curValue;
        //write  into array
        this->values_1[this->counter_1] = this->curValue_1;
        //cout << "Counter: " << this->counter_1 << "   |   " << curValue << " == " << curValue_1 <<"==" << values_1[this->counter_1] << endl;
        if (this->counter_1 == 99) this->counter_1 = 0;
        else this->counter_1++;
    } else {
        cout << "[ERROR] Buffer::setCurrentValue: unknown channel (" << channel << "|" << curValue << ")";
    }
}
//return average of current buffer to be displayed on window
float Buffer::calculatesAvg(int channel) {
    if (channel== 0) {
        int sum0 = 0;
        for (int i=0; i< 100; i++) sum0 += this->values_0[i];
        cout << "Channel: " << channel <<" Counter: " << this->counter_0 << "     | Cur: " << this->curValue_0 << "    |   " << (float)sum0 / 100. << "   | Sum: " << sum0 << endl;
        return (float)sum0 / 100.;
    } else if (channel== 1) {
        int sum1 = 0;
        for (int i=0; i< 100; i++) sum1 += this->values_1[i];
        cout << "Channel: " << channel <<" Counter: " << this->counter_1 << "     | Cur: " << this->curValue_1 << "    |   " << (float)sum1 / 100. << "   | Sum: " << sum1 << endl;
        return (float)sum1 / 100.;
    } else
    {
        cout << "Unknown Channel: " << channel << endl;
    }
}
