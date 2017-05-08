#include <QtGlobal>
#include <QDateTime>
#include <error.h>

#include "sbox.h"

SBox::SBox() : m_sbox(nullptr), m_fixedpoint(0)
{

}

void SBox::generation()
{
    generate(m_sbox);
}

void SBox::calculation()
{
    QPair<double, double> res;

    res = getValues(plus, plus);
    m_max.plusPlus = res.first;
    m_avr.plusPlus = res.second;

    res = getValues(plus, minus);
    m_max.plusMinus = res.first;
    m_avr.plusMinus = res.second;

    res = getValues(plus, XOR);
    m_max.plusXOR = res.first;
    m_avr.plusXOR = res.second;

    res = getValues(minus, plus);
    m_max.minusPlus = res.first;
    m_avr.minusPlus = res.second;

    res = getValues(minus, minus);
    m_max.minusMinus = res.first;
    m_avr.minusMinus = res.second;

    res = getValues(minus, XOR);
    m_max.minusXOR = res.first;
    m_avr.minusXOR = res.second;

    res = getValues(XOR, plus);
    m_max.xorPlus = res.first;
    m_avr.xorPlus = res.second;

    res = getValues(XOR, minus);
    m_max.xorMinus = res.first;
    m_avr.xorMinus = res.second;

    res = getValues(XOR, XOR);
    m_max.xorXOR = res.first;
    m_avr.xorXOR = res.second;

    m_fixedpoint = 0;
    for(int i = 0; i < 256; i++){
        if(m_sbox[i] == H(m_sbox[i])){
            m_fixedpoint++;
        }
    }
}

const SBox::RESULT SBox::getValuesMAX() const
{
    return m_max;
}

const SBox::RESULT SBox::getValuesAVR() const
{
    return m_avr;
}

const int SBox::getFixedPoint() const
{
    return m_fixedpoint;
}

void SBox::generate(byte *& sbox)
{
    if(sbox){
        delete[] (sbox);
    }

    sbox = new byte[256];
    for(int i = 0; i < 256; i++){
        (sbox)[i] = i;
    }

    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    for(int i = 255; i > 0; i--){
        std::swap((sbox)[i], (sbox)[qrand() % i]);
    }
}

const double SBox::getValue(const oper &oper1, const oper &oper2, const byte &alfa, const byte &betta)
{
    int count = 0;
    for(int k = 0; k < 256; k++) {
        count += isEqual(oper1( H( oper2(k, alfa) ), H(k) ), betta);
    }
    return count * CONST;
}

const QPair<double, double> SBox::getValues(const oper &oper1, const oper &oper2)
{
    QPair<double, double> result;
    double   max = 0.0;
    double total = 0.0;
    for(int alfa = 1; alfa < 256; alfa++) {
        for(int betta = 1; betta < 256; betta++) {
            const double value = getValue(oper1, oper2, alfa, betta);
            total += value;
            if(max < value){
                max = value;
            }
        }
    }

    result.first  = max;
    result.second = total / 65025.0;

    return result;
}

const byte SBox::H(const int value)
{
    if(!m_sbox){
        throw "Sbox didn`t generated, please call SBox::generation() before use";
    }

    return m_sbox[value];
}
