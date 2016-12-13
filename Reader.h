#include <iostream>
#include <thread>
#include <vector>

class Reader
{

public:
    // Constructor
    Reader();

    // Destructor
    ~Reader();

    // parseFile()
    // Arguments:
    // fileName: File to be parsed(path)
    // numThreads: Number of threads to use for parsing
    // Returns true if successful or false if not.
    bool parseFile(const char *fileName="example.txt", int numThreads=4);

    void printParsedLines();

private:
    const char *mFileName;
    int mNumThreads;
    std::vector<std::thread> mThreads;
    bool stop;

    class Buffer
    {
    public:
        Buffer() : isReady(false){}
        bool isReady;
        std::vector<std::string> lines;
    };

    void _processLines(int thId, Buffer *buffer);

    std::vector<std::string> parsedLines;
};

