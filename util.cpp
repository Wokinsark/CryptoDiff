#include "util.h"


const byte plus(const byte &a, const byte &b){
    return (byte)(a + b);
}

const byte minus(const byte &a, const byte &b){
    return (byte)(a - b);
}

const byte XOR(const byte &a, const byte &b){
    return (byte)(a ^ b);
}

const bool isEqual(const byte &a, const byte &b){
    return (bool)(a == b);
}

void append(QList<QPair<double, int> > &list, const double &value){
    for(int i = 0; i < list.length(); i++){
        if(value == list[i].first){
            list[i].second++;
            return;
        }
    }

    list.append(QPair<double, int>{ value, 1 });
}
