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

    const RESULT getP1MAX() const;
    const RESULT getP1AVR() const;

    const int    getP2MAX() const;
    const double getP2AVR() const;

    const RESULT getP3MAX() const;

    const int    getP4() const;

protected:

    virtual void generate(byte * &sbox);

private:

    const double getValueP1(const oper & oper1, const oper & oper2, const byte& alfa, const byte& betta);
    const int    getValueP2(const byte &  alfa, const byte & betta);
    const double getValueP3(const oper & oper1, const oper & oper2, const byte& alfa, const byte& betta);
    const int    getValueP4();

    const QPair<double, double> getValuesP1(const oper & oper1, const oper & oper2);
    const QPair<double, double> getValuesP2();
    const double                getValuesP3(const oper & oper1, const oper & oper2);


    const byte H(const int value);

    byte *    m_sbox;

    RESULT   m_maxP1;
    RESULT   m_avrP1;
    int      m_maxP2;
    double   m_avrP2;
    RESULT   m_maxP3;
    int      m_valP4;
};

#endif // SBOX_H
