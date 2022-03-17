#include "pack.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace jidantou;

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

// pack file into several files and entrypt
int PackFile(string fileName, int size, string key)
{
    unsigned long iFileSize;
    char * pbuff;
    int buffNum;
    string outputPath;
    
    ifstream * pfile = new ifstream(fileName, ios::binary | ios::in);
    ofstream * pOutputFile;

    if(pfile->fail())
        return 1;
    
    system(("mkdir " + fileName).c_str());

    // get the size of file
    pfile->seekg(ios::end);
    iFileSize = pfile->tellg();
    pfile->seekg(ios::beg);

    // get the number of output files
    buffNum = iFileSize / size;

    char c;

    for (int i = 0; i < buffNum; i++)
    {
        c = i + 65;
        outputPath = ".\\" + fileName + &c;
        
        pOutputFile = new ofstream(outputPath, ios::binary);

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
        c++;
        outputPath = ".\\" + fileName + &c;
        
        pOutputFile = new ofstream(outputPath, ios::binary);
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

    return 0;
}

// pack file into several files with no entrypting
int PackFile(string fileName, string path, int size);

// unpack files and restore with entrypting
int UnpackFiles(string fileName, string path, int size, string key);

// unpack files and restore with no entrypting
int UnpackFiles(string fileName, string path, int size);