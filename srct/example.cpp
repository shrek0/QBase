#include <iostream>

using namespace std;

#include "qbase.h"

int main()
{
    QString baseChars = "0123456789ABCDEF";
    QBase qbase(baseChars);

    qbase.step();

    return 0;
}

