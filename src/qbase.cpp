/****************************************************************************
**
**  QBase Copyright (C) 2014 shrek0.
**  Contact: shrek0tk(at)gmail.com
**
**  This program is free software: you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation, either version 3 of the License, or
**   (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
*****************************************************************************/

#include <QChar>
#include <QVector>

#include <cmath>

#include "qbase.h"


QBase::QBase(const QString &baseChars) {
    init(baseChars);
}

QBase::QBase(const QString &baseChars, qlonglong fromNumber) {
    init(baseChars);

    fromLong(fromNumber);
}

QBase::QBase(const QString &baseChars, QString &fromNumber) {
    init(baseChars);

    fromQString(fromNumber);
}

QBase::QBase(const QBase &inputQBase) {

}

QBase::~QBase() {
    erase();
}

void QBase::erase() {
    for(uint i = 0; i < d->digitsLen; ++i)
        delete pDigitsArray[i];

    delete[] pDigitsArray;
    delete d;
}

void QBase::init(const QString &baseChars) {
    d = new Data;

    d->baseChars = baseChars;
    d->base = baseChars.length();
    d->digitsMax = 5;

    d->longNumber = 0;
    d->digitsLen = 1;
    d->nextDigitAddition = d->base;

    pDigitsArray = new QBaseDigit*[d->digitsMax];
    pDigitsArray[0] = new QBaseDigit(d->base);

}

void QBase::clear() {
    erase();
    init(d->baseChars);
}

void QBase::fromLong(qlonglong fromNumber) {
    clear();

    // Turn minusFlag on if fromNumber less than zero.
    if(fromNumber < 0)
        d->minusFlag = true;
    else
        d->minusFlag = false;

    d->longNumber = fromNumber;

    convertLongToQString(fromNumber, d->qstringNumber);
    d->qstringCacheDigitsCahnged = d->qstringNumber.length();
}

const QString &QBase::toQString() {
    //if(d->qstringCacheDigitsCahnged == 0)
    //    return d->qstringNumber;

    if(d->minusFlag == true)
        for(uint i = 0; i < d->digitsLen; ++i)
            d->qstringNumber[d->digitsLen-i] = d->baseChars.at(-(pDigitsArray[i]->getDecimalNumber()));
    else
        for(uint i = 0; i < d->digitsLen; ++i)
            d->qstringNumber[d->digitsLen-i] = d->baseChars.at(pDigitsArray[i]->getDecimalNumber());

    d->qstringCacheDigitsCahnged = 0;

    return d->qstringNumber;

}

void QBase::fromQString(QString &fromNumber) {
    d->longNumber = 0;
    qulonglong temp = 0;

    clear();

    // Turn minusFlag on if the first letter in the string is '-'.
    if(fromNumber[0] == '-') {
        fromNumber.remove(0, 1);
        d->minusFlag = true;
    }else{
        d->minusFlag = false;
    }

    d->qstringNumber = fromNumber;
    convertQStringToLong(fromNumber, temp);

    d->longNumber = temp;

    d->qstringCacheDigitsCahnged = 1;
        // Install bases..
}

/**
 * @brief QBase::convertLongToQString
 * @param unsigned inputNumber to convert.
 * @param outputQString to convert.
 *
 * This function has a description in the documentation.
 */

void QBase::convertLongToQString(qulonglong inputNumber, QString &outputQString) {
    uint numberLength = 0;
    QChar tempVariable = 0;

    while(inputNumber) {
        outputQString += d->baseChars.at(inputNumber % d->base);

        inputNumber /=  d->base;
    }

    numberLength = outputQString.length();

    for(uint i = 0; i < numberLength/2 ;++i) {  // Reverse it.
        tempVariable = outputQString[numberLength-i-1];
        outputQString[numberLength-i-1] = outputQString[i];
        outputQString[i] = tempVariable;
    }
}

/**
 * @brief QBase::convertQStringToLong convert QString to long number.
 * @param unsigned inputQString (without minus character [='-']).
 * @param outputNumber unsigned long number.
 *
 * This function has a description in the documentation.
 */

void QBase::convertQStringToLong(const QString &inputQString, qulonglong &outputNumber) {
    uint numberLength = inputQString.length();
    qlonglong numberToMultiplication = pow(d->base , numberLength-1);

    for(uint i = 0; i < numberLength; ++i) {
        outputNumber += d->baseChars.indexOf(inputQString[i])
                * numberToMultiplication;

        numberToMultiplication /= d->base; //this is same as pow(base, pathInNumber-1)
    }
}

void QBase::step(int steps) {
    d->longNumber+=steps;

    if(-(d->longNumber) >= d->nextDigitAddition || d->longNumber >= d->nextDigitAddition)
        addNewDigit();

    pDigitsArray[0]->step(steps);

    if(d->minusFlag == false && d->longNumber < 0)
        d->minusFlag = true;
    else if(d->minusFlag == true && d->longNumber > 0)
        d->minusFlag = false;

    //d->qstringCacheDigitsCahnged=1;
}

/**
 * @brief QBase::realloc pDigitsArray and increase it to 5.
 */

void QBase::realloc() {
    QBaseDigit **new_pDigitsArray = new QBaseDigit*[d->digitsMax+5];

    for(uint i = 0; i < d->digitsLen; ++i)
        new_pDigitsArray[i] = pDigitsArray[i];

    d->digitsMax+=5;

    delete[] pDigitsArray;

    pDigitsArray = new_pDigitsArray;
}

void QBase::addNewDigit() {
    if(d->digitsLen == d->digitsMax)
        realloc();

    pDigitsArray[d->digitsLen] = new QBaseDigit(d->base);

    d->nextDigitAddition *= d->base;

    pDigitsArray[d->digitsLen-1]->addNextDigit(pDigitsArray[d->digitsLen]);

    d->qstringCacheDigitsCahnged++;

    d->digitsLen++;
}
