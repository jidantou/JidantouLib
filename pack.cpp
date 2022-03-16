#include "pack.h"
#include <iostream>
#include <fstream>

using namespace jidantou;

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

// pack file into several files and entrypt
int PackFile(string fileName, string filePath, int size, string key)
{
    unsigned long iFileSize;
    char * pbuff;
    int buffNum;
    
    ifstream * pfile = new ifstream(filePath, ios::binary | ios::in);
    ofstream * pOutputFile;

    if(pfile->fail())
        return 1;
    
    // get the size of file
    pfile->seekg(ios::end);
    iFileSize = pfile->tellg();
    pfile->seekg(ios::beg);

    // get the number of output files
    buffNum = iFileSize / size;

    for (int i = 0; i < buffNum; i++)
    {
        pOutputFile = new ofstream(filePath, ios::binary);

        if(!pOutputFile->fail())
        {
            pbuff = new char[size];
            
            pfile->read(pbuff, size);
            // deal with data in the file
            pOutputFile->write(pbuff, size);

            pOutputFile->close();
            delete [] pbuff;
        }
        else
        {
            // deal with error in output files
        }
        delete pOutputFile;
    }

    if(!pfile->eof())
    {
        pOutputFile = new ofstream(filePath, ios::binary);
        if(!pOutputFile->fail())
        {
            pbuff = new char[iFileSize - buffNum * size];

            pfile->read(pbuff, iFileSize - buffNum * size);
            // deal with data in the file
            pOutputFile->write(pbuff, iFileSize - buffNum * size);

            pOutputFile->close();
            delete [] pbuff;
        }
        else
        {
            // deal with error 
            // in the last output file
        }

        buffNum++;

        delete pOutputFile;
    }
    
    pfile->close();
    delete pfile;
}

// pack file into several files with no entrypting
int PackFile(string fileName, string path, int size);

// unpack files and restore with entrypting
int UnpackFiles(string fileName, string path, int size, string key);

// unpack files and restore with no entrypting
int UnpackFiles(string fileName, string path, int size);