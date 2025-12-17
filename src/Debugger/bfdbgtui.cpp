#include "bfdebugger.hpp"
#include <algorithm>
#include <iomanip>
inline void DebuggerRunPointer::printHex08(size_t num)
{
    std::cout<<std::uppercase<<std::hex<<std::setw(8)
        <<std::setfill('0')<<num<<std::dec;
} 
inline void DebuggerRunPointer::printHex02(size_t num)
{
    std::cout<<std::uppercase<<std::hex<<std::setw(2)
        <<std::setfill('0')<<num<<std::dec;
} 
void DebuggerRunPointer::showStatus()
{
    watchStatus info(runner->get_debugger_stat(RunnerPointer::DebugPermission{}));
    std::cout<<"==========================[CODE]==========================\n";
    int len=info.rocommands.cend()-info.rocommands.cbegin();
    int ipindex=info.rocodePointer-info.rocommands.cbegin()+1;
    for(auto i=-3;i<4;++i)
    {
        if(ipindex+i<1||ipindex+i>len)
        {
            std::cout<<std::endl;
            continue;
        }
        if(i==0)
            std::cout<<" IP -> ";
        else
            std::cout<<"       ";
        size_t curkey=ipindex+i;
        if(std::find(breakpoint.cbegin(),breakpoint.cend(),curkey-1)!=breakpoint.cend())
            std::cout<<"[!] #";
        else
            std::cout<<"[ ] #";
        printHex08(curkey);
        std::cout<<" at loc("<<(info.rocodePointer+i)->get_row()<<","
            <<(info.rocodePointer+i)->get_col()<<") : "
            <<(info.rocodePointer+i)->get_operate()<<std::endl;
    }
    std::cout<<"IP = #";
    printHex08(ipindex);
    std::cout<<" at loc("<<info.rocodePointer->get_row()<<","
            <<info.rocodePointer->get_col()<<") : "
            <<info.rocodePointer->get_operate()<<std::endl;
    std::cout<<"=========================================================="<<std::endl;
    std::cout<<"-------------------------[MEMORY]-------------------------"<<std::endl;
    int memlen=info.romemorySize;
    int mpindex=info.roitpos-info.romemory;
    for(auto i=-2;i<3;++i)
    {
        if(mpindex+i<0||mpindex+i>=memlen)
        {
            std::cout<<std::endl;
            continue;
        }
        std::cout<<"                  [";
        printHex02(*(info.roitpos+i));
        std::cout<<"] *";
        printHex08(mpindex+i);
        if(i==0)
            std::cout<<" <-- MP";
        std::cout<<std::endl;
    }
    std::cout<<"MP = *";
    printHex08(mpindex);
    std::cout<<std::endl;
    std::cout<<"----------------------------------------------------------"<<std::endl;
    std::cout<<"=========================[WATCH]=========================="<<std::endl;
    if(breakpoint.empty())
        std::cout<<" No breakpoint."<<std::endl;
    for(int bpi=0;bpi<breakpoint.size();++bpi)
    {
        std::cout<<" BP "<<bpi+1<<" at loc("<<info.rocommands[breakpoint[bpi]].get_row()
            <<","<<info.rocommands[breakpoint[bpi]].get_col()<<") : "
            <<info.rocommands[breakpoint[bpi]].get_operate()<<std::endl;
    }
    if(memWatch.empty())
        std::cout<<" No watched memory."<<std::endl;
    for(int wmi=0;wmi<memWatch.size();++wmi)
    {
        std::cout<<" MEM "<<wmi+1<<" *";
        printHex08(memWatch[wmi].cellCode);
        std::cout<<" : [";
        printHex02(*(info.romemory+memWatch[wmi].cellCode));
        std::cout<<"]"<<std::endl;
    }
    std::cout<<"=========================================================="<<std::endl;
}