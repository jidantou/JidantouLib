#include <iostream>
#include "stdio.h"
#include "fraction.h"

using namespace std;
using namespace Jidantou;

bool bigendian()
{
    uint16_t a = 0x1234;
    uint8_t *b = (uint8_t *) &a;
    printf("0x%X\n0x%X\n", &a, a);
    printf("0x%X\n0x%X\n", b, *b);
    //b = (uint8_t *)a;
    //if(*b == 0x34)
        return true;
    //else return false;
}

int main()
{
    fraction f2(0.2), f3(0.5);
    /*
    double val_d = 1.125;
    uint64_t val_64;
    val_64 = *(int64_t *)&val_d;
    printf("val_d:%f  val_64:%llu\n", val_d, val_64);
    */
    cout << f2 << endl << f3 << endl;
    // f3 += 0.2565;
    cout << f3 << endl;
    
    return 0;
}