#include <iostream>

using namespace std;

#include "qbase.h"

int main()
{
    QString baseChars = "01";
    QBase qbase(baseChars);

    for(uint i = 0; i < 100; ++i) {
        qbase.step();
        cout << qbase.toQString().toStdString() << endl;
    }

    return 0;
}

