#include "pack.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

// using namespace jidantou;

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

/* Better realization
#include <string>

using namespace std;
string IntToString(int val)
{
      int length = 0;
      bool Below = val < 0;
      string t = "";
      string ret = "";
      if(!val)
            return "0";
      if (Below)
      {
            val = -val;
            ret = "-";
      }
      while(val)
      {
            t = t + (char)(val % 10 + 48);
            val = val / 10;
            length++;
      }
      for(int j = 0; j < length; j++)
            ret = ret + t[length - j - 1];
      return ret;
}
int 
*/
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

    // get the number of output files
    buffNum = fileSize / size;

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