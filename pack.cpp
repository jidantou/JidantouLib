#include "pack.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

// DEBUG
// using namespace std;

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

string jidantou::IntToString(int64_t val)
    {
    int length = 0;
    int i = 0, j;
    string str = "";
    char temp;

    if(!val)
        return "0";
    if (val < 0)
    {
        val = -val;
        str = "-";
        i = 1;
    }
    // put ever number into str 
    while(val)
    {
        str = str + (char)(val % 10 + 48);
        val = val / 10;
        length++;
    }
    // change the order in str
    for(j = str.length() - 1; i < j; i++, j--)
    {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
    }
    return str;
}

/*
static char DecimalString[11] = "0123456789";
// turn int to std::string
string jidantou::IntToString(int64_t integer)
{
    string finalstr;
    char str[20] = {"0000000000000000000"};
    int i = 19, j;

    while (integer && i)
    {
        str[i] = DecimalString[integer % 10];
        integer /= 10;
        i--;
    }

    for(i = 0; str[i] == '0' && i < 20; i++);
    std::cout << i << std::endl;
    if(i == 20)
        finalstr = "0";
    else if(i == 0)
        finalstr = str;
    else
    {
        char * s = new char[20 - i];

        for(j = 0; i < 20; i++, j++)
        {
            s[j] = str[i];
        }
        finalstr = s;
        delete[] s;
    }
    return finalstr;
}
*/

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

    if(system(("mkdir " + fileName).c_str()) == -1)
        return 2;

    // get the size of file
    pfile->seekg(0, ios::end);
    fileSize = pfile->tellg();
    pfile->seekg(0, ios::beg);
    // DEBUG
    // cout << fileSize << endl;

    // get the number of output files
    buffNum = fileSize / size;
    // DEBUG
    // cout << "buffNum:" << buffNum << endl;

    for (int i = 0; i < buffNum; i++)
    {
        
        outputPath = ".\\" + fileName + "\\" + fileName + IntToString(i);
        
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

    // DEBUG
    // if(pfile->eof())
    //     cout << "pfile->eof()" << endl;

    if(fileSize % size)
    {
        if(!pfile->eof())
        {
            outputPath = ".\\" + fileName + "\\" + fileName + IntToString(buffNum);
            
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