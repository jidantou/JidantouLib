#include "pack.h"
#include <iostream>
#include <fstream>

using namespace jidantou;

using std::string;
using std::fstream;
using std::ios;

// pack file into several files and entrypt
bool PackFile(string fileName, string path, int size, string key)
{
    fstream * pfile = new fstream(fileName, ios::binary | ios::in | ios::_Nocreate);

    pfile->close();
    delete pfile;
}

// pack file into several files with no entrypting
bool PackFile(string fileName, string path, int size);

// unpack files and restore with entrypting
bool UnpackFiles(string fileName, string path, int size, string key);

// unpack files and restore with no entrypting
bool UnpackFiles(string fileName, string path, int size);