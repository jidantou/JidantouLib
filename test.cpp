#include <iostream>
#include <fstream>

#include "pack.h"

using namespace std;
using namespace jidantou;

int main()
{
    string str = IntToString(1234567890);
    // cout << PackFile(".\\test.txt", 1);
    cout << str << endl;
    cout << str[9] << "    " << str[10] << endl;
    cout << str.length() << endl;

    /*
    fstream file;
    // test.txt : abcdefghijklmn
    file.open(".\\test.txt", ios::ate | ios::in | ios::out |ios::binary);

    streampos length = 0;

    // file.seekp(ios::end);
    length = file.tellp();
    cout << "tellp:" << length << endl;
    // file.seekp(ios::beg);

    length = 0;

    file.seekg(0, ios::end);
    length = file.tellg();
    cout << "tellg:" << length << endl;
    // file.seekg(ios::beg);
    */

    return 0;
}