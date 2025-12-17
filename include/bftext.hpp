#ifndef _BFTEXT_
#define _BFTEXT_
#include <string>
#include <iostream>
#include <functional>
namespace BFtext
{
    extern const std::string VERSION;
    enum class ErrorType
    {
        normal=-1,
        fileErr=0,
        usageERR=1,
        memoryOF=2,
        stackOF=3,
        bucketMATCH=4
    };
    struct ErrorContext
    {
        char *programName=nullptr;
        char *fileName=nullptr;
        int mismatchRow=-1;
        int mismatchCol=-1;
    };
    extern const BFtext::ErrorContext null_content;
    extern const std::string fileError;
    extern const std::string memoryOverflow;
    extern const std::string stackOverflow;
    extern const std::string bucketCannotMatch;
    extern const std::string errorTitle;
    extern const std::string usagePrompt;
    extern const std::string exitTitle;
    extern const std::string exitMessage;
    extern const std::string *errMessage[];
    extern const std::string debugPrompt;
    extern const std::string debugUsage;
    extern const std::string debugHelp;
    void printUsage(std::ostream& os=std::cerr);
    void debuggerUsage(std::ostream& os=std::cerr);
    void printFatalError(ErrorType typeID,ErrorContext content=null_content,
        std::ostream& os=std::cerr);
    void terminateWithCode(unsigned char retcode,std::ostream& os=std::cout);
    void triggerBreakpoint(size_t bpid,size_t i,size_t j,std::ostream& os=std::cout);
}
#endif