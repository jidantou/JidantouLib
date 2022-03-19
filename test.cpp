#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream file;
    // test.txt : abcdefghijklmn
    file.open(".\\test.txt", ios::ate | ios::in | ios::out |ios::binary);

    streampos length = 0;

    // file.seekp(ios::end);
    length = file.tellp();
    cout << "tellp:" << length << endl;
    // file.seekp(ios::beg);

    length = 0;

    // file.seekg(ios::end);
    length = file.tellg();
    cout << "tellg:" << length << endl;
    // file.seekg(ios::beg);

    return 0;
}