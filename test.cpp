#include <iostream>
#include "fraction.h"

using namespace std;
using namespace Jidantou;


int main()
{
    fraction /*f1(3, 5, 0), f2(3.25545956),*/ f3(522);
    cout /*<< f1 << endl
        << f2 << endl*/
        << f3 << endl;
    f3 += 532.2565;
    cout << f3 << endl;

    return 0;
}