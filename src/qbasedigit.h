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

#ifndef QBASEDIGIT_H
#define QBASEDIGIT_H

#include <QtGlobal>

class QBaseDigit
{
public:
    QBaseDigit(uint base);

    int getDecimalNumber() { return decimalNumber; }
    void addNextDigit(QBaseDigit *pNextDigit);

    void step(int steps);

private:
    int decimalNumber;
    int base;
    QBaseDigit *pNextDigit;
};

#endif // QBASEDIGIT_H
