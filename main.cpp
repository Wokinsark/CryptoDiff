#include <QDebug>
#include <QCoreApplication>
#include <QString>

#include <math.h>
#include "sboxbelt.h"

#define MAX_COUNT 5

void printList(const QList<QPair<double, int>> & list, QString name){
    qDebug() << name;
    for(QPair<double, int> val : list){
        qDebug() << QString("VALUE - %1 (2 ^ %2) COUNT - %3").arg(val.first).arg(-log2(1/val.first)).arg(val.second);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SBoxBelT belT;
    belT.generation();
    belT.calculation();

    SBox::RESULT maxBelT = belT.getValuesMAX();
    SBox::RESULT avrBelT = belT.getValuesAVR();

    qDebug() << "*** --- *** BelIT *** --- ***";

    qDebug() << "*** --- *** MAXIMUM *** --- ***";

    qDebug() << QString("### ### PLUS PLUS   %1 (2 ^ %2)").arg(maxBelT.plusPlus).arg(-log2(1/maxBelT.plusPlus));
    qDebug() << QString("### ### PLUS MINUS  %1 (2 ^ %2)").arg(maxBelT.plusMinus).arg(-log2(1/maxBelT.plusMinus));
    qDebug() << QString("### ### PLUS XOR    %1 (2 ^ %2)").arg(maxBelT.plusXOR).arg(-log2(1/maxBelT.plusXOR));

    qDebug() << QString("### ### MINUS PLUS  %1 (2 ^ %2)").arg(maxBelT.minusPlus).arg(-log2(1/maxBelT.minusPlus));
    qDebug() << QString("### ### MINUS MINUS %1 (2 ^ %2)").arg(maxBelT.minusMinus).arg(-log2(1/maxBelT.minusMinus));
    qDebug() << QString("### ### MINUS XOR   %1 (2 ^ %2)").arg(maxBelT.minusXOR).arg(-log2(1/maxBelT.minusXOR));

    qDebug() << QString("### ### XOR PLUS    %1 (2 ^ %2)").arg(maxBelT.xorPlus).arg(-log2(1/maxBelT.xorPlus));
    qDebug() << QString("### ### XOR MINUS   %1 (2 ^ %2)").arg(maxBelT.xorMinus).arg(-log2(1/maxBelT.xorMinus));
    qDebug() << QString("### ### XOR XOR     %1 (2 ^ %2)").arg(maxBelT.xorXOR).arg(-log2(1/maxBelT.xorXOR));

    qDebug() << "*** --- *** AVERAGE *** --- ***";

    qDebug() << QString("### ### PLUS PLUS   %1 (2 ^ %2)").arg(avrBelT.plusPlus).arg(-log2(1/avrBelT.plusPlus));
    qDebug() << QString("### ### PLUS MINUS  %1 (2 ^ %2)").arg(avrBelT.plusMinus).arg(-log2(1/avrBelT.plusMinus));
    qDebug() << QString("### ### PLUS XOR    %1 (2 ^ %2)").arg(avrBelT.plusXOR).arg(-log2(1/avrBelT.plusXOR));

    qDebug() << QString("### ### MINUS PLUS  %1 (2 ^ %2)").arg(avrBelT.minusPlus).arg(-log2(1/avrBelT.minusPlus));
    qDebug() << QString("### ### MINUS MINUS %1 (2 ^ %2)").arg(avrBelT.minusMinus).arg(-log2(1/avrBelT.minusMinus));
    qDebug() << QString("### ### MINUS XOR   %1 (2 ^ %2)").arg(avrBelT.minusXOR).arg(-log2(1/avrBelT.minusXOR));

    qDebug() << QString("### ### XOR PLUS    %1 (2 ^ %2)").arg(avrBelT.xorPlus).arg(-log2(1/avrBelT.xorPlus));
    qDebug() << QString("### ### XOR MINUS   %1 (2 ^ %2)").arg(avrBelT.xorMinus).arg(-log2(1/avrBelT.xorMinus));
    qDebug() << QString("### ### XOR XOR     %1 (2 ^ %2)").arg(avrBelT.xorXOR).arg(-log2(1/avrBelT.xorXOR));

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

    for(int i = 0; i < MAX_COUNT; i++){
        qDebug() << "progress " << i;

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

    return a.exec();
}
