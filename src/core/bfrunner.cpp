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
            if(*itpos==0)
                codePointer=commands.begin()+(codePointer->get_match()-&commands[0])-1;
            bucketStack.push(codePointer);
            if(bucketStack.size()>stackSize)
                status=BFtext::ErrorType::memoryOF;
            break;
        case ']':
            if(*itpos)
                codePointer=commands.begin()+(codePointer->get_match()-&commands[0])-1;
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
    {
        sourceCode+=cur;
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
            case '+': case '-': case '>': case '<':
            case '[': case ']': case ',': case '.':
                commands.emplace_back(currow,curcol,cur);
                ++curcol;
                break;
            default:
                break;
        }
    }
    std::stack<Instructer *> bracket;
    Instructer *temp;
    bool unmatch=false;
    for(auto &ins:commands)
    {
        switch(ins.get_operate())
        {
            case '[':
                bracket.push(&ins);
                break;
            case ']':
                if(bracket.empty())
                {
                    details.mismatchCol=ins.get_col();
                    details.mismatchRow=ins.get_row();
                    unmatch=true;
                    break;
                }
                temp=bracket.top();
                ins.set_match(temp);
                temp->set_match(&ins);
                bracket.pop();
                break;
            default:
                break;
        }
        if(unmatch)
            break;
    }
    if(!bracket.empty())
    {
        details.mismatchCol=commands.back().get_col();
        details.mismatchRow=commands.back().get_row();
        unmatch=true;
    }
    if(unmatch)
    {
        BFtext::printFatalError(BFtext::ErrorType::bucketMATCH,details);
        return false;
    }
    codePointer=commands.begin();
    return true;
}