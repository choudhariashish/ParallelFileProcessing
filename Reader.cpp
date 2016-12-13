#include "Reader.h"
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
    std::string line;
    Buffer buffer[mNumThreads];    
    int currBuffIndex = 0;

    if (mNumThreads<1)
    {
        std::cout<<"Needs more than 1 thread for parsing"<<std::endl;
        return false;
    }    


    // Create threads
    for (int thId = 0; thId < mNumThreads; ++thId)
    {
        mThreads.push_back(std::thread(&Reader::_processLines, this));
    }

    std::ifstream inptFile(mFileName);
    if (inptFile.is_open() )
    {
        while ( getline(inptFile, line) )
        {
            buffer[currBuffIndex].lines.push_back( line );

	    // Change buffer if needed and mark current buffer as ready.
	    if ( 5 == currBuffIndex )
	    {
	        int temp = currBuffIndex;
	        currBuffIndex = (currBuffIndex + 1) % mNumThreads; 
	        buffer[temp].isReady = true;
	    }
	}
	// Check if current buffer has some remaining lines, if so, then
	// process them here.
	while ( buffer[currBuffIndex].lines.size() )
	{
	    std::vector<std::string> l = buffer[currBuffIndex].lines;
            std::cout<<l.front()<<std::endl;
	    l.erase(l.begin(), l.begin()+1);
	}
        inptFile.close();
    }
    else
    {
        std::cout<<"Failed to open file"<<std::endl;
        return false;
    }

    // Join threads
    for (int thId = 0; thId < mNumThreads; ++thId)
    {
        mThreads[thId].join();
    }
    return true;
}


void Reader::_processLines()
{
    std::cout<<"Hello"<<std::endl;
}