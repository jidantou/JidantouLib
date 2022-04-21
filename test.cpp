#include <iostream>
#include <fstream>

#include "fraction.h"

using namespace std;
using namespace Jidantou;

int main()
{

    fraction<int> f1, f2(2, 3);

    f1 = f2;

    f1.output();
    f2.output();

    return 0;
}