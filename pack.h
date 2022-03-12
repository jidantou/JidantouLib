#ifndef PACK_H
#define PACK_H

#include <iostream>
using std::string;

namespace jidantou
{
    // pack file into several files and entrypt
    bool PackFile(string fileName, string path, int size, string key);

    // pack file into several files with no entrypting
    bool PackFile(string fileName, string path, int size);

    // unpack files and restore with entrypting
    bool UnpackFiles(string fileName, string path, int size, string key);

    // unpack files and restore with no entrypting
    bool UnpackFiles(string fileName, string path, int size);
}
#endif