#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include <QDateTime>

#include <math.h>

#include "sboxbelt.h"
#include "sboxgrig.h"

#define MAX_COUNT 10000

void printList(const QList<QPair<double, int>> & list, QString name){
    qDebug() << name;
    for(QPair<double, int> val : list){
        qDebug() << QString("VALUE - %1 (2 ^ %2) COUNT - %3").arg(QString::number(val.first, 'f', 9)).arg(-log2(1/val.first)).arg(val.second);
    }
}

void printList(const QList<QPair<double, int>> & list){
    for(QPair<double, int> val : list){
        qDebug() << QString("VALUE - %1 COUNT - %2").arg(QString::number(val.first, 'f', 9)).arg(val.second);
    }
}

void printSBox(const SBox & sbox, QString name){
     qDebug() << QString("*** --- *** %1 *** --- ***").arg(name);

     const SBox::RESULT maxP1 = sbox.getP1MAX();
     const SBox::RESULT avrP1 = sbox.getP1AVR();
     const int          maxP2 = sbox.getP2MAX();
     const double       avrP2 = sbox.getP2AVR();
     const SBox::RESULT maxP3 = sbox.getP3MAX();

     qDebug() << "*** --- *** POINT 1 (MAXIMUM) *** --- ***";

     qDebug() << QString("### ### PLUS PLUS   %1 (2 ^ %2)").arg(maxP1.plusPlus).arg(-log2(1/maxP1.plusPlus));
     qDebug() << QString("### ### PLUS MINUS  %1 (2 ^ %2)").arg(maxP1.plusMinus).arg(-log2(1/maxP1.plusMinus));
     qDebug() << QString("### ### PLUS XOR    %1 (2 ^ %2)").arg(maxP1.plusXOR).arg(-log2(1/maxP1.plusXOR));

     qDebug() << QString("### ### MINUS PLUS  %1 (2 ^ %2)").arg(maxP1.minusPlus).arg(-log2(1/maxP1.minusPlus));
     qDebug() << QString("### ### MINUS MINUS %1 (2 ^ %2)").arg(maxP1.minusMinus).arg(-log2(1/maxP1.minusMinus));
     qDebug() << QString("### ### MINUS XOR   %1 (2 ^ %2)").arg(maxP1.minusXOR).arg(-log2(1/maxP1.minusXOR));

     qDebug() << QString("### ### XOR PLUS    %1 (2 ^ %2)").arg(maxP1.xorPlus).arg(-log2(1/maxP1.xorPlus));
     qDebug() << QString("### ### XOR MINUS   %1 (2 ^ %2)").arg(maxP1.xorMinus).arg(-log2(1/maxP1.xorMinus));
     qDebug() << QString("### ### XOR XOR     %1 (2 ^ %2)").arg(maxP1.xorXOR).arg(-log2(1/maxP1.xorXOR));

     qDebug() << "*** --- *** POINT 1 (AVERAGE) *** --- ***";

     qDebug() << QString("### ### PLUS PLUS   %1 (2 ^ %2)").arg(avrP1.plusPlus).arg(-log2(1/avrP1.plusPlus));
     qDebug() << QString("### ### PLUS MINUS  %1 (2 ^ %2)").arg(avrP1.plusMinus).arg(-log2(1/avrP1.plusMinus));
     qDebug() << QString("### ### PLUS XOR    %1 (2 ^ %2)").arg(avrP1.plusXOR).arg(-log2(1/avrP1.plusXOR));

     qDebug() << QString("### ### MINUS PLUS  %1 (2 ^ %2)").arg(avrP1.minusPlus).arg(-log2(1/avrP1.minusPlus));
     qDebug() << QString("### ### MINUS MINUS %1 (2 ^ %2)").arg(avrP1.minusMinus).arg(-log2(1/avrP1.minusMinus));
     qDebug() << QString("### ### MINUS XOR   %1 (2 ^ %2)").arg(avrP1.minusXOR).arg(-log2(1/avrP1.minusXOR));

     qDebug() << QString("### ### XOR PLUS    %1 (2 ^ %2)").arg(avrP1.xorPlus).arg(-log2(1/avrP1.xorPlus));
     qDebug() << QString("### ### XOR MINUS   %1 (2 ^ %2)").arg(avrP1.xorMinus).arg(-log2(1/avrP1.xorMinus));
     qDebug() << QString("### ### XOR XOR     %1 (2 ^ %2)").arg(avrP1.xorXOR).arg(-log2(1/avrP1.xorXOR));

     qDebug() << "*** --- *** POINT 2 *** --- ***";

     qDebug() << "### ### MAXIMUM " << maxP2;
     qDebug() << "### ### AVERAGE " << avrP2;

     qDebug() << "*** --- *** POINT 3 (MAXIMUM) *** --- ***";

     qDebug() << QString("### ### PLUS PLUS   %1 (2 ^ %2)").arg(maxP3.plusPlus).arg(-log2(1/maxP3.plusPlus));
     qDebug() << QString("### ### PLUS MINUS  %1 (2 ^ %2)").arg(maxP3.plusMinus).arg(-log2(1/maxP3.plusMinus));
     qDebug() << QString("### ### PLUS XOR    %1 (2 ^ %2)").arg(maxP3.plusXOR).arg(-log2(1/maxP3.plusXOR));

     qDebug() << QString("### ### MINUS PLUS  %1 (2 ^ %2)").arg(maxP3.minusPlus).arg(-log2(1/maxP3.minusPlus));
     qDebug() << QString("### ### MINUS MINUS %1 (2 ^ %2)").arg(maxP3.minusMinus).arg(-log2(1/maxP3.minusMinus));
     qDebug() << QString("### ### MINUS XOR   %1 (2 ^ %2)").arg(maxP3.minusXOR).arg(-log2(1/maxP3.minusXOR));

     qDebug() << QString("### ### XOR PLUS    %1 (2 ^ %2)").arg(maxP3.xorPlus).arg(-log2(1/maxP3.xorPlus));
     qDebug() << QString("### ### XOR MINUS   %1 (2 ^ %2)").arg(maxP3.xorMinus).arg(-log2(1/maxP3.xorMinus));
     qDebug() << QString("### ### XOR XOR     %1 (2 ^ %2)").arg(maxP3.xorXOR).arg(-log2(1/maxP3.xorXOR));

     qDebug() << "*** --- *** POINT 4 (FIXED POINT) *** --- ***";

     qDebug() << sbox.getP4();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SBoxBelT belT;
    SBoxGrig grig;

    belT.generation();
    belT.calculation();
    printSBox(belT, "BelIT");

    grig.generation();
    grig.calculation();
    printSBox(grig, "Grig");

    QList<QPair<double, int>> point1PlusPlusMAX;
    QList<QPair<double, int>> point1PlusMinusMAX;
    QList<QPair<double, int>> point1PlusXORMAX;

    QList<QPair<double, int>> point1MinusPlusMAX;
    QList<QPair<double, int>> point1MinusMinusMAX;
    QList<QPair<double, int>> point1MinusXORMAX;

    QList<QPair<double, int>> point1XORPlusMAX;
    QList<QPair<double, int>> point1XORMinusMAX;
    QList<QPair<double, int>> point1XORXORMAX;

    QList<QPair<double, int>> point1PlusPlusAVR;
    QList<QPair<double, int>> point1PlusMinusAVR;
    QList<QPair<double, int>> point1PlusXORAVR;

    QList<QPair<double, int>> point1MinusPlusAVR;
    QList<QPair<double, int>> point1MinusMinusAVR;
    QList<QPair<double, int>> point1MinusXORAVR;

    QList<QPair<double, int>> point1XORPlusAVR;
    QList<QPair<double, int>> point1XORMinusAVR;
    QList<QPair<double, int>> point1XORXORAVR;

    QList<QPair<double, int>> point2MAX;
    QList<QPair<double, int>> point2AVR;

    QList<QPair<double, int>> point3PlusPlusMAX;
    QList<QPair<double, int>> point3PlusMinusMAX;
    QList<QPair<double, int>> point3PlusXORMAX;

    QList<QPair<double, int>> point3MinusPlusMAX;
    QList<QPair<double, int>> point3MinusMinusMAX;
    QList<QPair<double, int>> point3MinusXORMAX;

    QList<QPair<double, int>> point3XORPlusMAX;
    QList<QPair<double, int>> point3XORMinusMAX;
    QList<QPair<double, int>> point3XORXORMAX;

    QList<QPair<double, int>> point4;

    qint64 start = 0;

    for(int i = 1; i <= MAX_COUNT; i++){

        qDebug() << QString("%1 from %2 (left %3) delta - %4 ms").arg(i).arg(MAX_COUNT).arg(MAX_COUNT - i).arg(start ? QDateTime::currentDateTime().toMSecsSinceEpoch() - start : 0);
        start = QDateTime::currentDateTime().toMSecsSinceEpoch();

        SBox sbox;
        sbox.generation();
        sbox.calculation();

        const SBox::RESULT maxP1 = sbox.getP1MAX();
        const SBox::RESULT avrP1 = sbox.getP1AVR();
        const    int       maxP2 = sbox.getP2MAX();
        const double       avrP2 = sbox.getP2AVR();
        const SBox::RESULT maxP3 = sbox.getP3MAX();
        const int          valP4 = sbox.getP4();

        append(point1PlusPlusMAX,  maxP1.plusPlus);
        append(point1PlusMinusMAX, maxP1.plusMinus);
        append(point1PlusXORMAX,   maxP1.plusXOR);

        append(point1MinusPlusMAX,  maxP1.minusPlus);
        append(point1MinusMinusMAX, maxP1.minusMinus);
        append(point1MinusXORMAX,   maxP1.minusXOR);

        append(point1XORPlusMAX,  maxP1.xorPlus);
        append(point1XORMinusMAX, maxP1.xorMinus);
        append(point1XORXORMAX,   maxP1.xorXOR);

        append(point1PlusPlusAVR,  avrP1.plusPlus);
        append(point1PlusMinusAVR, avrP1.plusMinus);
        append(point1PlusXORAVR,   avrP1.plusXOR);

        append(point1MinusPlusAVR,  avrP1.minusPlus);
        append(point1MinusMinusAVR, avrP1.minusMinus);
        append(point1MinusXORAVR,   avrP1.minusXOR);

        append(point1XORPlusAVR,  avrP1.xorPlus);
        append(point1XORMinusAVR, avrP1.xorMinus);
        append(point1XORXORAVR,   avrP1.xorXOR);

        append(point2MAX, maxP2);
        append(point2AVR, avrP2);

        append(point3PlusPlusMAX,  maxP3.plusPlus);
        append(point3PlusMinusMAX, maxP3.plusMinus);
        append(point3PlusXORMAX,   maxP3.plusXOR);

        append(point3MinusPlusMAX,  maxP3.minusPlus);
        append(point3MinusMinusMAX, maxP3.minusMinus);
        append(point3MinusXORMAX,   maxP3.minusXOR);

        append(point3XORPlusMAX,  maxP3.xorPlus);
        append(point3XORMinusMAX, maxP3.xorMinus);
        append(point3XORXORMAX,   maxP3.xorXOR);

        append(point4, valP4);
    }

    qDebug() << "*** --- *** POINT 1 (MAXIMUM) *** --- ***";

    printList(point1PlusPlusMAX,  "### ### PLUS PLUS ");
    printList(point1PlusMinusMAX, "### ### PLUS MINUS ");
    printList(point1PlusXORMAX,   "### ### PLUS XOR ");

    printList(point1MinusPlusMAX,  "### ### MINUS PLUS ");
    printList(point1MinusMinusMAX, "### ### MINUS MINUS ");
    printList(point1MinusXORMAX,   "### ### MINUS XOR ");

    printList(point1XORPlusMAX,  "### ### XOR PLUS ");
    printList(point1XORMinusMAX, "### ### XOR MINUS ");
    printList(point1XORXORMAX,   "### ### XOR XOR ");

    qDebug() << "*** --- *** POINT 1 (AVERAGE) *** --- ***";

    printList(point1PlusPlusAVR,  "### ### PLUS PLUS ");
    printList(point1PlusMinusAVR, "### ### PLUS MINUS ");
    printList(point1PlusXORAVR,   "### ### PLUS XOR ");

    printList(point1MinusPlusAVR,  "### ### MINUS PLUS ");
    printList(point1MinusMinusAVR, "### ### MINUS MINUS ");
    printList(point1MinusXORAVR,   "### ### MINUS XOR ");

    printList(point1XORPlusAVR,  "### ### XOR PLUS ");
    printList(point1XORMinusAVR, "### ### XOR MINUS ");
    printList(point1XORXORAVR,   "### ### XOR XOR ");

    qDebug() << "*** --- *** POINT 2 (MAXIMUM) *** --- ***";

    printList(point2MAX);

    qDebug() << "*** --- *** POINT 2 (AVERAGE) *** --- ***";

    printList(point2AVR);

    qDebug() << "*** --- *** POINT 3 (MAXIMUM) *** --- ***";

    printList(point3PlusPlusMAX,  "### ### PLUS PLUS ");
    printList(point3PlusMinusMAX, "### ### PLUS MINUS ");
    printList(point3PlusXORMAX,   "### ### PLUS XOR ");

    printList(point3MinusPlusMAX,  "### ### MINUS PLUS ");
    printList(point3MinusMinusMAX, "### ### MINUS MINUS ");
    printList(point3MinusXORMAX,   "### ### MINUS XOR ");

    printList(point3XORPlusMAX,  "### ### XOR PLUS ");
    printList(point3XORMinusMAX, "### ### XOR MINUS ");
    printList(point3XORXORMAX,   "### ### XOR XOR ");

    qDebug() << "*** --- *** POINT 4 (FIXED POINT) *** --- ***";

    printList(point4);

    return a.exec();
}
