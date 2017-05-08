#ifndef SBOXBELT_H
#define SBOXBELT_H

#include "sbox.h"

class SBoxBelT : public SBox
{
public:
    SBoxBelT();

protected:
    void generate(byte ** sbox);
};

#endif // SBOXBELT_H
