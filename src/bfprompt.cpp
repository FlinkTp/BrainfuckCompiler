#include "../include/bftext.hpp"
#include <iostream>
namespace BFtext
{
    void printUsage(std::ostream& os)
    {
        os<<usagePrompt<<std::endl;
    }
    void printFatalError(ErrorType typeID,ErrorContext content,std::ostream& os)
    {
        if(typeID!=ErrorType::fileErr)
            os<<std::endl<<errorTitle<<std::endl;
        switch(typeID)
        {
            case ErrorType::fileErr:
                os<<content.programName<<fileError<<content.fileName<<std::endl;
                break;
            case ErrorType::bucketMATCH:
                os<<bucketCannotMatch<<" loc=("<<content.mismatchRow<<":"
                    <<content.mismatchCol<<")"<<std::endl;
                break;
            default:
                os<<errMessage[static_cast<size_t>(typeID)]<<std::endl;
                break;
        }
    }
    void terminateWithCode(unsigned char retcode,std::ostream& os)
    {
        os<<std::endl<<exitTitle<<std::endl;
        os<<exitMessage<<static_cast<int>(retcode)<<std::endl;
    }
}