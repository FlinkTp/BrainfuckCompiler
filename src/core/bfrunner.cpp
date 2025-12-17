#include "bfconfig.hpp"
#include "bftext.hpp"
#include <fstream>
int RunnerPointer::singlestep()
{
    if(itpos<memory.get())
        return 0;
    if(codePointer==commands.end())
        return *itpos;
    if(itpos==memory.get()+memorySize)
    {
        status=BFtext::ErrorType::memoryOF;
        return -1;
    }
    decltype(codePointer) stackTop; 
    switch(codePointer->get_operate())
    {
        case '+':
            ++*itpos;
            break;
        case '-':
            --*itpos;
            break;
        case '>':
            ++itpos;
            break;
        case '<':
            --itpos;
            break;
        case ',':
            *itpos=getchar();
            break;
        case '.':
            putchar(*itpos);
            break;
        case '[':
            bucketStack.push(codePointer);
            if(bucketStack.size()>stackSize)
                status=BFtext::ErrorType::memoryOF;
            break;
        case ']':
            if(bucketStack.empty())
            {
                status=BFtext::ErrorType::bucketMATCH;
                details.mismatchCol=codePointer->get_col();
                details.mismatchRow=codePointer->get_row();
                break;
            }
            if(*itpos)
                codePointer=bucketStack.top()-1;
            else
            {
                stackTop=bucketStack.top();
                while(!bucketStack.empty()&&bucketStack.top()==stackTop)
                    bucketStack.pop();
            }
            break;
        default:
            break;
    }
    ++codePointer;
    return -1;
}
int RunnerPointer::runAll()
{
    int retVal=-1;
    while(retVal==-1&&status==BFtext::ErrorType::normal)
        retVal=singlestep();
    return retVal;
}
bool RunnerPointer::loadFile(const char *filePath,const char *progName)
{
    std::ifstream fin(filePath);
    if(fin.fail())
    {
        BFtext::ErrorContext fileFail;
        fileFail.programName=const_cast<char *>(progName);
        fileFail.fileName=const_cast<char *>(filePath);
        BFtext::printFatalError(BFtext::ErrorType::fileErr,fileFail);
        return false;
    }
    char cur;
    int currow=1,curcol=1,i;
    while(fin.get(cur))
        switch(cur)
        {
            case '\t':
                for(i=1;i<=4;++i)
                    commands.emplace_back(currow,curcol,' '),++curcol;
                break;
            case '\n':
                ++currow;
                curcol=1;
                break;
            default:
                commands.emplace_back(currow,curcol,cur);
                ++curcol;
                break;
        }
    codePointer=commands.begin();
    return true;
}