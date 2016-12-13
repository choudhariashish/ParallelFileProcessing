#include "Reader.h"
#include <fstream>
#include <string>


Reader::Reader() :
    mFileName(NULL),
    mNumThreads(0),
    stop(false)
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
        mThreads.push_back(std::thread(&Reader::_processLines, this, thId, &buffer[thId]));
    }

    std::ifstream inptFile(mFileName);
    if (inptFile.is_open() )
    {
        while ( getline(inptFile, line) )
        {
            buffer[currBuffIndex].lines.push_back(line);

            // Check if buffer is ready to be processed by thread.
            if(buffer[currBuffIndex].lines.size()==1000)
            {
                std::cout<<"Filled:"<<currBuffIndex<<std::endl;
                buffer[currBuffIndex].isReady=true;
            }

            // Find new buffer to fill.
            while(buffer[currBuffIndex].isReady)
            {
                currBuffIndex=(currBuffIndex+1)%mNumThreads;
            }
	    }
        inptFile.close();
    }
    else
    {
        std::cout<<"Failed to open file"<<std::endl;
        return false;
    }


    while(buffer[currBuffIndex].lines.size() != 0)
    {
        //
        //  Process remaining lines here
        //


        buffer[currBuffIndex].lines.erase(buffer[currBuffIndex].lines.begin());
    }


    // Signal all threads to stop
    stop = true;


    // Join threads
    for (int thId = 0; thId < mNumThreads; ++thId)
    {
        mThreads[thId].join();
    }

    return true;
}


//
// Thread function
//
void Reader::_processLines(int thId, Buffer *buffer)
{
    std::cout<<"ThId:"<<thId<<std::endl;
    while (false==stop)
    {
        if(buffer->isReady)
        {
            //
            //  Process lines here
            //


            // Clear the line once processed
            buffer->lines.erase(buffer->lines.begin());
            if(buffer->lines.size()==0) buffer->isReady=false;
        }
    }
}


void Reader::printParsedLines()
{
    while(parsedLines.size())
    {
        std::cout<<parsedLines.front()<<std::endl;
        parsedLines.erase(parsedLines.begin());
    }
}
