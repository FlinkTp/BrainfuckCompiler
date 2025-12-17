#include "bfconfig.hpp"
#include "bftext.hpp"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
constructCFG concfg;
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
    if(!codeRunner.loadFile(argv[1],argv[0]))
        return -1;
    int result=codeRunner.runAll();
    if(codeRunner.get_status()==BFtext::ErrorType::normal)
        BFtext::terminateWithCode(result);
    else
        BFtext::printFatalError(codeRunner.get_status(),codeRunner.get_stat_detail());
    return result;
}