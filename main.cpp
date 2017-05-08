#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include <QDateTime>

#include <math.h>

#include "sboxbelt.h"
#include "sboxgrig.h"

#define MAX_COUNT 1000

void printList(const QList<QPair<double, int>> & list, QString name){
    qDebug() << name;
    for(QPair<double, int> val : list){
        qDebug() << QString("VALUE - %1 (2 ^ %2) COUNT - %3").arg(val.first).arg(-log2(1/val.first)).arg(val.second);
    }
}

void printList(const QList<QPair<double, int>> & list){
    for(QPair<double, int> val : list){
        qDebug() << QString("VALUE - %1 COUNT - %2").arg(val.first).arg(val.second);
    }
}

void printSBox(const SBox & sbox, QString name){
     qDebug() << QString("*** --- *** %1 *** --- ***").arg(name);

     const SBox::RESULT max = sbox.getValuesMAX();
     const SBox::RESULT avr = sbox.getValuesAVR();

     qDebug() << "*** --- *** MAXIMUM *** --- ***";

     qDebug() << QString("### ### PLUS PLUS   %1 (2 ^ %2)").arg(max.plusPlus).arg(-log2(1/max.plusPlus));
     qDebug() << QString("### ### PLUS MINUS  %1 (2 ^ %2)").arg(max.plusMinus).arg(-log2(1/max.plusMinus));
     qDebug() << QString("### ### PLUS XOR    %1 (2 ^ %2)").arg(max.plusXOR).arg(-log2(1/max.plusXOR));

     qDebug() << QString("### ### MINUS PLUS  %1 (2 ^ %2)").arg(max.minusPlus).arg(-log2(1/max.minusPlus));
     qDebug() << QString("### ### MINUS MINUS %1 (2 ^ %2)").arg(max.minusMinus).arg(-log2(1/max.minusMinus));
     qDebug() << QString("### ### MINUS XOR   %1 (2 ^ %2)").arg(max.minusXOR).arg(-log2(1/max.minusXOR));

     qDebug() << QString("### ### XOR PLUS    %1 (2 ^ %2)").arg(max.xorPlus).arg(-log2(1/max.xorPlus));
     qDebug() << QString("### ### XOR MINUS   %1 (2 ^ %2)").arg(max.xorMinus).arg(-log2(1/max.xorMinus));
     qDebug() << QString("### ### XOR XOR     %1 (2 ^ %2)").arg(max.xorXOR).arg(-log2(1/max.xorXOR));

     qDebug() << "*** --- *** AVERAGE *** --- ***";

     qDebug() << QString("### ### PLUS PLUS   %1 (2 ^ %2)").arg(avr.plusPlus).arg(-log2(1/avr.plusPlus));
     qDebug() << QString("### ### PLUS MINUS  %1 (2 ^ %2)").arg(avr.plusMinus).arg(-log2(1/avr.plusMinus));
     qDebug() << QString("### ### PLUS XOR    %1 (2 ^ %2)").arg(avr.plusXOR).arg(-log2(1/avr.plusXOR));

     qDebug() << QString("### ### MINUS PLUS  %1 (2 ^ %2)").arg(avr.minusPlus).arg(-log2(1/avr.minusPlus));
     qDebug() << QString("### ### MINUS MINUS %1 (2 ^ %2)").arg(avr.minusMinus).arg(-log2(1/avr.minusMinus));
     qDebug() << QString("### ### MINUS XOR   %1 (2 ^ %2)").arg(avr.minusXOR).arg(-log2(1/avr.minusXOR));

     qDebug() << QString("### ### XOR PLUS    %1 (2 ^ %2)").arg(avr.xorPlus).arg(-log2(1/avr.xorPlus));
     qDebug() << QString("### ### XOR MINUS   %1 (2 ^ %2)").arg(avr.xorMinus).arg(-log2(1/avr.xorMinus));
     qDebug() << QString("### ### XOR XOR     %1 (2 ^ %2)").arg(avr.xorXOR).arg(-log2(1/avr.xorXOR));

     qDebug() << "*** --- *** FIXED POINT *** --- ***";

     qDebug() << sbox.getFixedPoint();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SBoxBelT belT;
    SBoxGrig grig;

    belT.generation();
    grig.generation();

    belT.calculation();
    grig.calculation();

    printSBox(belT, "BelIT");
    printSBox(grig, "Grig");


    QList<QPair<double, int>> plusplusMAX;
    QList<QPair<double, int>> plusminusMAX;
    QList<QPair<double, int>> plusxorMAX;

    QList<QPair<double, int>> minusplusMAX;
    QList<QPair<double, int>> minusminusMAX;
    QList<QPair<double, int>> minusxorMAX;

    QList<QPair<double, int>> xorplusMAX;
    QList<QPair<double, int>> xorminusMAX;
    QList<QPair<double, int>> xorxorMAX;

    QList<QPair<double, int>> plusplusAVR;
    QList<QPair<double, int>> plusminusAVR;
    QList<QPair<double, int>> plusxorAVR;

    QList<QPair<double, int>> minusplusAVR;
    QList<QPair<double, int>> minusminusAVR;
    QList<QPair<double, int>> minusxorAVR;

    QList<QPair<double, int>> xorplusAVR;
    QList<QPair<double, int>> xorminusAVR;
    QList<QPair<double, int>> xorxorAVR;

    QList<QPair<double, int>> fixedPoint;

    qint64 start = 0;

    for(int i = 1; i <= MAX_COUNT; i++){

        qDebug() << QString("%1 from %2 (left %3) delta - %4 ms").arg(i).arg(MAX_COUNT).arg(MAX_COUNT - i).arg(start ? QDateTime::currentDateTime().toMSecsSinceEpoch() - start : 0);
        start = QDateTime::currentDateTime().toMSecsSinceEpoch();

        SBox sbox;
        sbox.generation();
        sbox.calculation();

        SBox::RESULT max = sbox.getValuesMAX();
        SBox::RESULT avr = sbox.getValuesAVR();

        append(plusplusMAX,  max.plusPlus);
        append(plusminusMAX, max.plusMinus);
        append(plusxorMAX,   max.plusXOR);

        append(minusplusMAX,  max.minusPlus);
        append(minusminusMAX, max.minusMinus);
        append(minusxorMAX,   max.minusXOR);

        append(xorplusMAX,  max.xorPlus);
        append(xorminusMAX, max.xorMinus);
        append(xorxorMAX,   max.xorXOR);

        append(plusplusAVR,  avr.plusPlus);
        append(plusminusAVR, avr.plusMinus);
        append(plusxorAVR,   avr.plusXOR);

        append(minusplusAVR,  avr.minusPlus);
        append(minusminusAVR, avr.minusMinus);
        append(minusxorAVR,   avr.minusXOR);

        append(xorplusAVR,  avr.xorPlus);
        append(xorminusAVR, avr.xorMinus);
        append(xorxorAVR,   avr.xorXOR);

        append(fixedPoint, sbox.getFixedPoint());
    }

    qDebug() << "*** --- *** MAXIMUM *** --- ***";

    printList(plusplusMAX,  "### ### PLUS PLUS ");
    printList(plusminusMAX, "### ### PLUS MINUS ");
    printList(plusxorMAX,   "### ### PLUS XOR ");

    printList(minusplusMAX,  "### ### MINUS PLUS ");
    printList(minusminusMAX, "### ### MINUS MINUS ");
    printList(minusxorMAX,   "### ### MINUS XOR ");

    printList(xorplusMAX,  "### ### XOR PLUS ");
    printList(xorminusMAX, "### ### XOR MINUS ");
    printList(xorxorMAX,   "### ### XOR XOR ");

    qDebug() << "*** --- *** AVERAGE *** --- ***";

    printList(plusplusAVR,  "### ### PLUS PLUS ");
    printList(plusminusAVR, "### ### PLUS MINUS ");
    printList(plusxorAVR,   "### ### PLUS XOR ");

    printList(minusplusAVR,  "### ### MINUS PLUS ");
    printList(minusminusAVR, "### ### MINUS MINUS ");
    printList(minusxorAVR,   "### ### MINUS XOR ");

    printList(xorplusAVR,  "### ### XOR PLUS ");
    printList(xorminusAVR, "### ### XOR MINUS ");
    printList(xorxorAVR,   "### ### XOR XOR ");

    qDebug() << "*** --- *** FIXED POINT *** --- ***";

    printList(fixedPoint);

    return a.exec();
}
