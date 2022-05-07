#include <iostream>
#include <fstream>

#include "fraction.h"

using namespace std;
using namespace Jidantou;

class a
{
    friend int tella(a a1);
private:
    int i;
public:
    a(int num){i = num;}
    ~a() {}
};

int tella(a a1)
{
    return a1.i;
}


int main()
{

    a a1(10);
    cout << tella(a1);
    //fraction<int> f1, f2(2, 3);

    //f1 = f2;

    //f1.output();
    //f2.output();

    return 0;
}