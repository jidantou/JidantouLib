#include <iostream>
#include "stdio.h"
#include "fraction.h"

using namespace std;
using namespace Jidantou;

int main()
{
    fraction f1(100, 300), f2(4, 3, 1), f3;

    cout << "Please input f3:\n";
    cin >> f3;
    cout << "f1:" << f1.operator std::streamoff() << endl
         << "f2:" << f2.operator double() << endl
         << "f3:" << f3 << endl;
    // int64_t i;
    // cin >> i;
    // cout << "i:" << i << endl;

    return 0;
}