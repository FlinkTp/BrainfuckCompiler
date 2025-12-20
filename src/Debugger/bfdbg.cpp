#include "bfconfig.hpp"
#include "bfdebugger.hpp"
#include "bftext.hpp"
#include <limits>
#include <sstream>
constructCFG concfg;
std::map<std::string,CommandHandler> commandTable;
static void initializeHandler()
{
    commandTable["a"]=
    commandTable["stat"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>&){
        dbgMain.showStatus();
    };
    commandTable["s"]=
    commandTable["step"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>&){
        int tmp=dbgMain.runSingleStep();
        int ret=dbgMain.checkStatus(tmp);
        dbgMain.showStatus();
    };
    commandTable["n"]=
    commandTable["next"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>&){
        int tmp=dbgMain.runSingleStep();
        int ret=dbgMain.checkStatus(tmp);
    };
    commandTable["help"]=[&](DebuggerRunPointer&,const std::vector<std::string>&){
        std::cout<<BFtext::debugHelp<<std::endl;
    };
    commandTable["x"]=
    commandTable["continue"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>&){
        int tmp=dbgMain.runContinue();
        int ret=dbgMain.checkStatus(tmp);
        dbgMain.showStatus();
    };
    commandTable["b"]=
    commandTable["bp"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>& ins){
        if(ins.size()>2)
            std::cout<<"Invalid operation."<<std::endl;
        else
        {
            int bpindex=std::stoi(ins[1],nullptr,16);
            if(dbgMain.addBreakpoint(bpindex))
                std::cout<<"Added breakpoint."<<std::endl;
            else
                std::cout<<"Invalid operation."<<std::endl;
        }
    };
    commandTable["db"]=
    commandTable["debp"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>& ins){
        if(ins.size()>2)
            std::cout<<"Invalid operation."<<std::endl;
        else
        {
            int bpindex=std::stoi(ins[1]);
            if(dbgMain.cancelBreakpoint(bpindex-1))
                std::cout<<"Canceled breakpoint."<<std::endl;
            else
                std::cout<<"Invalid operation."<<std::endl;
        }
    };
    commandTable["w"]=
    commandTable["watch"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>& ins){
        if(ins.size()>2)
            std::cout<<"Invalid operation."<<std::endl;
        else
        {
            int wpindex=std::stoi(ins[1],nullptr,16);
            if(dbgMain.addWatchmemory(wpindex))
                std::cout<<"Added watch-memory."<<std::endl;
            else
                std::cout<<"Invalid operation."<<std::endl;
        }
    };
    commandTable["dw"]=
    commandTable["dewatch"]=[&](DebuggerRunPointer& dbgMain,const std::vector<std::string>& ins){
        if(ins.size()>2)
            std::cout<<"Invalid operation."<<std::endl;
        else
        {
            int wpindex=std::stoi(ins[1],nullptr,16);
            if(dbgMain.cancelWatchmemory(wpindex))
                std::cout<<"Canceled watch-memory."<<std::endl;
            else
                std::cout<<"Invalid operation."<<std::endl;
        }
    };
}
static int setConfig(int opNum,char *value)
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
static int processArgument(int argc,char *argv[])
{
    if(argc<=1||argc&1)
    {
        BFtext::debuggerUsage();
        return -1;
    }
    if(argc<=1||argc&1)
    {
        BFtext::debuggerUsage();
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
            BFtext::debuggerUsage();
            return -1;
        }
    }
    return 0;
}
static void printWelcome() 
{
    std::cout<<"Brainfuck Debugger "<<BFtext::VERSION<<"\n"
    "Copyright (C) 2025 FlinkTp\n"
    "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.\n\n"
    "Type 'help' for a list of commands.\n"
    "For bug reporting, see: https://github.com/FlinkTp/BrainfuckCompiler/issues\n\n";
}
static std::vector<std::string> splitTokens(const std::string input)
{
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string tok;
    while(iss>>tok)
        tokens.push_back(tok);
    return tokens;
}
static int processInstruction(DebuggerRunPointer& drp,std::string operation)
{
    if(operation=="quit"||operation=="exit")
        return 1;
    auto tokens=splitTokens(operation);
    if(tokens.empty()) 
        return 2;
    auto it=commandTable.find(tokens[0]);
    if(it==commandTable.end()) 
    {
        std::cout<<"Unknown command: "<<tokens[0]<<std::endl;
        return 2;
    }
    if(drp.failed()&&tokens[0]!="stat")
    {
        std::cout<<"Invalid operation: program terminated or failed."<<std::endl;
        return 2;
    }
    it->second(drp,tokens);
    return 0;
}
int main(int argc,char *argv[])
{
    if(processArgument(argc,argv))
        return -1;
    printWelcome();
    RunnerPointer dbgRunner(concfg);
    if(!dbgRunner.loadFile(argv[1],argv[0]))
        return -1;
    DebuggerRunPointer dbgMain(&dbgRunner);
    initializeHandler();
    std::string prev("");
    while(true)
    {
        std::string input;
        std::cout<<BFtext::debugPrompt<<std::flush;
        std::getline(std::cin,input);
        if(input==""&&prev!="")
            input=prev;
        int procres=processInstruction(dbgMain,input);
        if(procres==1)
            break;
        else if(procres)
            prev="";
        else
            prev=input;
    }
}