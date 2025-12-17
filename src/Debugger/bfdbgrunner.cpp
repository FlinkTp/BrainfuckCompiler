#include "bfdebugger.hpp"
#include <algorithm>
#include <iomanip>
bool DebuggerRunPointer::addBreakpoint(size_t bp)
{
    watchStatus info(runner->get_debugger_stat(RunnerPointer::DebugPermission{}));
    if(bp>=0&&bp<info.rocommands.size())
        breakpoint.emplace_back(bp-1);
    else
        return false;
    return true;
}
bool DebuggerRunPointer::cancelBreakpoint(size_t indx)
{
    if(indx>=breakpoint.size()||indx<0)
        return false;
    breakpoint.erase(breakpoint.begin()+indx);
    return true;
}
bool DebuggerRunPointer::addWatchmemory(size_t wp,Watchstrategy strat)
{
    watchStatus info(runner->get_debugger_stat(RunnerPointer::DebugPermission{}));
    if(wp>=0&&wp<info.romemorySize)
        memWatch.emplace_back(WatchedMem{static_cast<int>(wp),strat});
    else
        return false;
    return true;
}
bool DebuggerRunPointer::cancelWatchmemory(size_t indx)
{
    watchStatus info(runner->get_debugger_stat(RunnerPointer::DebugPermission{}));
    if(indx>=info.romemorySize||indx<0)
        return false;
    memWatch.erase(memWatch.begin()+indx);
    return true;
}
int DebuggerRunPointer::runSingleStep()
{
    if(stat==DebugStatus::breakpoint)
        stat=DebugStatus::normal;
    int resval=runner->singlestep();
    watchStatus info(runner->get_debugger_stat(RunnerPointer::DebugPermission{}));
    if(std::find(breakpoint.cbegin(),breakpoint.cend(),
        (info.rocodePointer-info.rocommands.begin()))!=breakpoint.cend())
    {
        stat=DebugStatus::breakpoint;
        return -3;
    }
    if(resval==-1&&runner->get_status()==BFtext::ErrorType::normal)
        return -2;
    if(runner->get_status()==BFtext::ErrorType::normal)
    {
        stat=DebugStatus::finish;
        return resval;
    }
    stat=DebugStatus::error;
    return -1;
}
int DebuggerRunPointer::runContinue()
{
    int resval;
    do
    {
        resval=runSingleStep();
    }while(stat==DebugStatus::normal);
    return resval;
}
int DebuggerRunPointer::checkStatus(int retval)
{
    watchStatus info(runner->get_debugger_stat(RunnerPointer::DebugPermission{}));
    int codeReturn,bpnum;
    switch(stat)
    {
        case DebugStatus::finish:
            BFtext::terminateWithCode(retval);
            codeReturn=1;
            break;
        case DebugStatus::error:
            BFtext::printFatalError(info.rostatus,info.rodetails);
            codeReturn=2;
            break;
        case DebugStatus::breakpoint:
            bpnum=std::find(breakpoint.cbegin(),breakpoint.cend(),
                (info.rocodePointer-info.rocommands.begin()))-breakpoint.cbegin();
            BFtext::triggerBreakpoint(bpnum,info.rocommands[breakpoint[bpnum]].get_row(),
                info.rocommands[breakpoint[bpnum]].get_col());
            codeReturn=3;
            break;
        case DebugStatus::normal:
            codeReturn=0;
    }
    if(codeReturn==1||codeReturn==2)
        fail=true;
    return codeReturn;
}