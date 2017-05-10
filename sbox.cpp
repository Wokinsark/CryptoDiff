#include <QtGlobal>
#include <QDateTime>
#include <error.h>

#include "sbox.h"

SBox::SBox() : m_sbox(nullptr), m_valP4(0)
{

}

void SBox::generation()
{
    generate(m_sbox);
}

void SBox::calculation()
{
    if(!m_sbox){
        throw "Sbox didn`t generated, please call SBox::generation() before use";
    }

    /// POINT 1

    QPair<double, double> resP1;

    resP1 = getValuesP1(plus, plus);
    m_maxP1.plusPlus = resP1.first;
    m_avrP1.plusPlus = resP1.second;

    resP1 = getValuesP1(plus, minus);
    m_maxP1.plusMinus = resP1.first;
    m_avrP1.plusMinus = resP1.second;

    resP1 = getValuesP1(plus, XOR);
    m_maxP1.plusXOR = resP1.first;
    m_avrP1.plusXOR = resP1.second;

    resP1 = getValuesP1(minus, plus);
    m_maxP1.minusPlus = resP1.first;
    m_avrP1.minusPlus = resP1.second;

    resP1 = getValuesP1(minus, minus);
    m_maxP1.minusMinus = resP1.first;
    m_avrP1.minusMinus = resP1.second;

    resP1 = getValuesP1(minus, XOR);
    m_maxP1.minusXOR = resP1.first;
    m_avrP1.minusXOR = resP1.second;

    resP1 = getValuesP1(XOR, plus);
    m_maxP1.xorPlus = resP1.first;
    m_avrP1.xorPlus = resP1.second;

    resP1 = getValuesP1(XOR, minus);
    m_maxP1.xorMinus = resP1.first;
    m_avrP1.xorMinus = resP1.second;

    resP1 = getValuesP1(XOR, XOR);
    m_maxP1.xorXOR = resP1.first;
    m_avrP1.xorXOR = resP1.second;

    /// POINT 2

    QPair<double, double> resP2 = getValuesP2();
    m_maxP2 = resP2.first;
    m_avrP2 = resP2.second;

    /// POINT 3

    m_maxP3.plusPlus  = getValuesP3(plus, plus);
    m_maxP3.plusMinus = getValuesP3(plus, minus);
    m_maxP3.plusXOR   = getValuesP3(plus, XOR);

    m_maxP3.minusPlus  = getValuesP3(minus, plus);
    m_maxP3.minusMinus = getValuesP3(minus, minus);
    m_maxP3.minusXOR   = getValuesP3(minus, XOR);

    m_maxP3.xorPlus  = getValuesP3(XOR, plus);
    m_maxP3.xorMinus = getValuesP3(XOR, minus);
    m_maxP3.xorXOR   = getValuesP3(XOR, XOR);

    /// POINT 4

    m_valP4 = getValueP4();
}

const SBox::RESULT SBox::getP1MAX() const
{
    return m_maxP1;
}

const SBox::RESULT SBox::getP1AVR() const
{
    return m_avrP1;
}

const int SBox::getP2MAX() const
{
    return m_maxP2;
}

const double SBox::getP2AVR() const
{
    return m_avrP2;
}

const SBox::RESULT SBox::getP3MAX() const
{
    return m_maxP3;
}

const int SBox::getP4() const
{
    return m_valP4;
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

const double SBox::getValueP1(const oper &oper1, const oper &oper2, const byte &alfa, const byte &betta)
{
    int count = 0;
    for(int k = 0; k < 256; k++) {
        count += isEqual(oper1( H( oper2(k, alfa) ), H(k) ), betta);
    }
    return count * CONST;
}

const int SBox::getValueP2(const byte &alfa, const byte &betta)
{
    int value = 0;
    for(int x = 0; x < 256; x++) {
        value += scalar(betta, H(x)) ^ scalar(alfa, x);
    }
    return value;
}

const double SBox::getValueP3(const oper &oper1, const oper &oper2, const byte &alfa, const byte &betta)
{
    return getValueP1(oper1, oper2, alfa, betta);
}

const int SBox::getValueP4()
{
    int res = 0;
    for(int i = 0; i < 256; i++){
        if(m_sbox[i] == H(m_sbox[i])){
            res++;
        }
    }

    return res;
}

const QPair<double, double> SBox::getValuesP1(const oper &oper1, const oper &oper2)
{
    QPair<double, double> result;
    double   max = 0.0;
    double total = 0.0;
    for(int alfa = MIN_ALFA; alfa <= MAX_ALFA; alfa++) {
        for(int betta = MIN_BETTA; betta <= MAX_BETTA; betta++) {
            const double value = getValueP1(oper1, oper2, alfa, betta);
            total += value;
            if(max < value){
                max = value;
            }
        }
    }

    result.first  = max;
    result.second = total / COUNT_ALFA_BETTA;

    return result;
}

const QPair<double, double> SBox::getValuesP2()
{
    QPair<double, double> result;
    int   max = 0;
    int total = 0;
    for(int alfa = MIN_ALFA; alfa <= MAX_ALFA; alfa++) {
        for(int betta = MIN_BETTA; betta <= MAX_BETTA; betta++) {
            const int value = getValueP2(alfa, betta);
            total += value;
            if(max < value){
                max = value;
            }
        }
    }

    result.first  = max;
    result.second = total / COUNT_ALFA_BETTA;

    return result;
}

const double SBox::getValuesP3(const oper &oper1, const oper &oper2)
{
    double   max = 0.0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            const double alfa  = pow(2, i);
            const double betta = pow(2, j);
            const double value = getValueP3(oper1, oper2, alfa, betta);
            if(max < value){
                max = value;
            }
        }
    }

    return max;
}

const byte SBox::H(const int value)
{
    return m_sbox[value];
}
