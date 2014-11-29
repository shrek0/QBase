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

#include "qbasedigit.h"

QBaseDigit::QBaseDigit(uint base) {
    this->base = base;
    decimalNumber = 0;
}

/**
 * @brief QBaseDigit::step and increment the next number.
 * @param steps to increment.
 */
void QBaseDigit::step(int steps) {
    steps = decimalNumber + steps;

    decimalNumber = (steps % base);

    if(steps >= base || -(steps) >= base)
        pNextDigit->step(steps / base);

}

void QBaseDigit::addNextDigit(QBaseDigit *pNextDigit) {
    this->pNextDigit = pNextDigit;
}
