#ifndef PACK_H
#define PACK_H

#include <iostream>
using std::string;

namespace jidantou
{   
    string IntToString(int64_t val);

    // pack file into several files and entrypt
    int PackFile(string fileName, int size);

    // pack file into several files with no entrypting
    int PackFile(string fileName, string path, int size);

    // unpack files and restore with entrypting
    int UnpackFiles(string fileName, string path, int size, string key);

    // unpack files and restore with no entrypting
    int UnpackFiles(string fileName, string path, int size);
}
#endif