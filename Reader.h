

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
    bool parseFile(const char *fileName="example.txt", int numThreads=1);

private:
    const char *mFileName;
    int mNumThreads;
};

