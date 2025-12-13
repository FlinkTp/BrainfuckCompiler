#include "../../include/bfconfig.hpp"
#include "../bfprompt.cpp"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
constructCFG concfg;
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
int setConfig(int opNum,char *value)
{
    int setValue=atoi(value);
    if(setValue<=0)
    {
        BFtext::printUsage();
        return 1;
    }
    switch(opNum)
    {
        case 0:
            concfg.memsize=setValue;
            break;
        case 1:
            concfg.stksize=setValue;
            break;
        case 3:
            concfg.codelen=setValue;
            break;
    }
    return 0;
}
void RunnerPointer::loadFile(const char *filePath,const char *progName)
{
    std::ifstream fin(filePath);
    if(fin.fail())
    {
        BFtext::ErrorContext fileFail;
        fileFail.programName=const_cast<char *>(progName);
        fileFail.fileName=const_cast<char *>(filePath);
        BFtext::printFatalError(BFtext::ErrorType::fileErr,fileFail);
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
}
int main(int argc,char *argv[])
{
    if(argc<=1||argc&1)
    {
        BFtext::printUsage();
        return -1;
    }
    for(int argi=2;argi<argc;argi+=2)
    {
        bool flagMatch=0;
        for(int i=0;i<argMapSize;++i)
            if(strcmp(argv[argi],argKey[i])==0||strcmp(argv[argi],argValue[i])==0)
            {
                if(setConfig(i,argv[argi+1])==1)
                    return -1;
                flagMatch=1;
            }
        if(!flagMatch)
        {
            BFtext::printUsage();
            return -1;
        }
    }
    RunnerPointer codeRunner(concfg);
    codeRunner.loadFile(argv[1],argv[0]);
    int result=codeRunner.runAll();
    if(codeRunner.get_status()==BFtext::ErrorType::normal)
        BFtext::terminateWithCode(result);
    else
        BFtext::printFatalError(codeRunner.get_status(),codeRunner.get_stat_detail());
    return result;
}