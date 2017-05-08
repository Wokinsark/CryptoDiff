#ifndef SBOX_H
#define SBOX_H

#include <QPair>

#include "util.h"

class SBox
{
public:

    struct RESULT{
        double plusPlus;
        double plusMinus;
        double plusXOR;

        double minusPlus;
        double minusMinus;
        double minusXOR;

        double xorPlus;
        double xorMinus;
        double xorXOR;
    };

    SBox();

    void generation();
    void calculation();

    RESULT getValuesMAX();
    RESULT getValuesAVR();

protected:

    virtual void generate(byte ** sbox);
    const double getValue(const oper & oper1, const oper & oper2, const byte& alfa, const byte& betta);
    const QPair<double, double> getValues(const oper & oper1, const oper & oper2);
    const byte H(const int value);

private:
    byte * m_sbox;

    RESULT m_max;
    RESULT m_avr;
};

#endif // SBOX_H
