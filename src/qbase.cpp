/****************************************************************************
**
**  QBase Copyright (C) 2014 shrek0.
**  Contact: shrek0tk(at)mail.com
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

#include "qbase.h"

#include <QChar>

#include <cmath>

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
    delete d;
}

void QBase::init(const QString &baseChars) {
    d = new Data;

    d->baseChars = baseChars;
    d->base = baseChars.length();
    d->digitsMax = 5;

    d->longNumber = 0;
    d->digitsLen = 1;

    //pDigitsArray = new QBaseDigit*[DigitsMax];
    //pDigitsArray[0] = QBaseDigit(base,chars);
}

void QBase::clear() {
    erase();
    init(d->baseChars);
}

void QBase::fromLong(qlonglong fromNumber) {
    clear();

    // Turn minusFlag on if fromNumber less than zero.
    if(fromNumber < 0) {
        d->longNumber = -(fromNumber);
        d->minusFlag = true;
    }else{
        d->longNumber = fromNumber;
        d->minusFlag = false;
    }

    convertLongToQString(fromNumber, d->qstringNumber);
}

void QBase::fromQString(QString &fromNumber) {
    d->longNumber = 0;

    clear();

    // Turn minusFlag on if the first letter in the string is '-'.
    if(fromNumber[0] == '-') {
        fromNumber.remove(0, 1);
        d->minusFlag = true;
    }else{
        d->minusFlag = false;
    }

    d->qstringNumber = fromNumber;
    convertQStringToLong(fromNumber, d->longNumber);

        // Install bases..
}

/**
 * @brief QBase::convertLongToQString convert long number to string.
 * @param unsigned inputNumber to convert.
 * @param outputQString to convert.
 *
 * This function has a description in the documentation.
 */
void QBase::convertLongToQString(const qulonglong inputNumber, QString &outputQString) {
    uint numberLength = 0;
    QChar tempVariable = 0;

    while(inputNumber) {
        outputQString += baseChars.at(inputNumber % base);

        inputNumber /=  base;
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

void QBase::step(uint steps) {
    pDigitsArray[0]->step(steps);
}
