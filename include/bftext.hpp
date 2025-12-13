#ifndef _BFTEXT_
#define _BFTEXT_
#include <string>
namespace BFtext
{
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
    }null_content;
    const std::string fileError=": Cannot open ";
    const std::string memoryOverflow="[FATAL] memory OVERFLOW!";
    const std::string stackOverflow="[FATAL] Segment Fault: Stack OVERFLOW!";
    const std::string bucketCannotMatch="[FATAL] a \']\' cannot match \'[\'!";
    const std::string errorTitle="!====================================!";
    const std::string usagePrompt=
    "usage: bfi <FILE> [-m <value> | --memory <value>]\n"
    "                  [-c <value> | --code <value>]\n"
    "                  [-s <value> | --stack <value>]\n"
    "                  [-l <value> | --line <value>]";
    const std::string exitTitle="-----------------------------------------------------------";
    const std::string exitMessage="Brainfuck Program successfully Terminated! Exitcode = ";
    const std::string *errMessage[]={&fileError,&usagePrompt,&memoryOverflow,
        &stackOverflow,&bucketCannotMatch};
    void printUsage(std::ostream& os=std::cerr);
    void printFatalError(ErrorType typeID,ErrorContext content=null_content,
        std::ostream& os=std::cerr);
    void terminateWithCode(unsigned char retcode,std::ostream& os=std::cout);
}
#endif