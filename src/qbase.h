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

#ifndef QBASE_H
#define QBASE_H

#include <QtGlobal>
#include <QString>

#include "qbasedigit.h"

class QBase
{
public:
    QBase(const QString &baseChars);
    QBase(const QString &baseChars, qlonglong fromNumber);
    QBase(const QString &baseChars, QString &fromNumber);
    QBase(const QBase &inputQBase);

    ~QBase();

    qulonglong toLong();
    const QString &toQString();
    const char *toCharArray();

    uint getBase() { return d->base; }

    void fromLong(qlonglong fromNumber);
    void fromQString(QString &fromNumber);

    void clear();

    void step(uint steps = 1);

private:
    void init(const QString &baseChars);
    void erase();

    void addNewDigit();

    void convertLongToQString(const qulonglong inputNumber, QString &outputQString);
    void convertQStringToLong(const QString &inputQString, qulonglong &outputNumber);

    QBaseDigit *pDigitsArray[];

    struct Data {
        uint base;
        QString baseChars;

        qulonglong longNumber;
        QString qstringNumber;

        uint digitsMax;
        uint digitsLen;

        bool minusFlag;

        qulonglong nextDigitAddition;
    };

    Data *d;

    typedef Data * DataPtr;
    inline DataPtr &data_ptr() { return d; }

};

#endif // QBASE_H
