#include "Reader.h"
#include <iostream>
#include <fstream>
#include <string>

Reader::Reader()
{
}

Reader::~Reader()
{
}

bool Reader::parseFile(const char *fileName, int numThreads)
{
    mFileName = fileName;
    mNumThreads = numThreads;
    std::string lineBuffer;

    if (mNumThreads<1)
    {
        std::cout<<"Needs more than 1 thread for parsing"<<std::endl;
        return false;
    }

    std::ifstream inptFile(mFileName);
    if (inptFile.is_open() )
    {
        while ( getline(inptFile, lineBuffer) )
        {
            std::cout<<lineBuffer<<std::endl;
        }
        inptFile.close();
    }
    else
    {
        std::cout<<"Failed to open file"<<std::endl;
        return false;
    }
    return true;
}
