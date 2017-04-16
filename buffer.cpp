#include "buffer.h"
#include <iostream>

using namespace std;

Buffer::Buffer()
{
    cout << "Buffer created" << endl;
    this->curValue_22 = 0;
    for (int i=0; i < 100; i++ ){
        this->values_22[i] = 0;
        this->counter_22 = 0;
    }

}

void Buffer::test(){
    cout << "Test function is running" << endl;
 }

void Buffer::setCurrentValue(int channel, int curValue) {
    if (channel == 22) {
        this->curValue_22 = curValue;
        this->values_22[this->counter_22] = this->curValue_22;
        //cout << "Counter: " << this->counter_22 << "   |   " << curValue << " == " << curValue_22 <<"==" << values_22[this->counter_22] << endl;
        if (this->counter_22 == 99) this->counter_22 = 0;
                else this->counter_22++;
    } else if (channel == 27) {
        cout << "To be done" << endl;
    } else {
        cout << "[ERROR] Buffer::setCurrentValue: unknown channel (" << channel << "|" << curValue << ")";
    }
}

float Buffer::calculatesAvg(int channel) {
    if (channel== 22) {
        int sum = 0;
        for (int i=0; i< 100; i++) sum += this->values_22[i];
        cout << "Counter: " << this->counter_22 << "     | Cur: " << this->curValue_22 << "    |   " << (float)sum / 100. << "   | Sum: " << sum << endl;
        return (float)sum / 100.;
    } else {
        cout << "Channel tbd" << endl;
    }
}
