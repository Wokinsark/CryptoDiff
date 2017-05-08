#ifndef SBOXGRIG_H
#define SBOXGRIG_H

#include "sbox.h"

class SBoxGrig : public SBox
{
public:
    SBoxGrig();

protected:
    void generate(byte *& sbox);
};

#endif // SBOXGRIG_H
