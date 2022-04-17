#include <iostream>
#include <fstream>

#include "pack.h"

using namespace std;
using namespace Jidantou;

int main()
{
    ofstream test("test.txt", ios::out);
    for (int i = 0; i < 21; i++)
    {
        test << IntToString(i) << "\n";
    }
    test.close();
    
    cout << PackFile(".\\test.txt", 3) << endl;
    return 0;
}