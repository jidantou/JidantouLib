#include "pack.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

// using namespace jidantou;

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

// pack file into several files and entrypt
int jidantou::PackFile(string fileName, int size)
{
    unsigned long fileSize;
    char * pbuff;
    int buffNum;
    string outputPath;
    
    ifstream * pfile = new ifstream(fileName, ios::binary | ios::in);
    ofstream * pOutputFile;

    if(pfile->fail())
        return 1;
    
    if(fileName.find('.') == string::npos)
        return 3;

    fileName.erase(fileName.find_last_of('.'), fileName.length());

    //if(system(("mkdir " + fileName).c_str()) == -1)
        //return 2;

    // get the size of file
    pfile->seekg(ios::end);
    fileSize = pfile->tellg();
    pfile->seekg(ios::beg);

    // get the number of output files
    buffNum = fileSize / size;

    char c[3] = {'0', '0', '\0'};

    for (int i = 0; i < buffNum; i++)
    {
        
        c[0] = i / 10 + 48;
        c[1] = i % 10 + 48;

        outputPath = ".\\" + fileName + "\\" + fileName + c;
        
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
        outputPath = ".\\" + fileName + "\\" + fileName + "_last";
        
        pOutputFile = new ofstream(outputPath, ios::binary);
        if(!pOutputFile->fail())
        {
            pbuff = new char[fileSize - buffNum * size];

            pfile->read(pbuff, fileSize - buffNum * size);
            // deal with data in the file
            pOutputFile->write(pbuff, fileSize - buffNum * size);

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