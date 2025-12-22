#ifndef _BFCONFIG_
#define _BFCONFIG_
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <memory>
#include <cstring>
#include <map>
#include "bftext.hpp"
class DebuggerRunPointer;
struct constructCFG
{
    int stksize=65535;
    int codelen=65535;
    size_t memsize=65535;
};
class Instructer
{
public:
    Instructer(int row,int col,char op,Instructer* next=nullptr): 
        rowNumber(row),colNumber(col),operate(op),matchBracket(next) {}
    char get_operate() const
    { return operate; }
    int get_row() const
    { return rowNumber; }
    int get_col() const
    { return colNumber; }
    void set_match(Instructer *mat)
    { matchBracket=mat; }
    Instructer *get_match() const
    { return matchBracket; }
private:
    int rowNumber;
    int colNumber;
    char operate;
    Instructer *matchBracket;
};
struct watchStatus
{
    watchStatus(const unsigned char *rom,const unsigned char *roit,const size_t roms,
        const std::vector<Instructer>::iterator rocp,const std::vector<Instructer>& roc,
        const BFtext::ErrorType rost,const BFtext::ErrorContext rodt) :
        romemory(rom),roitpos(roit),romemorySize(roms),rocodePointer(rocp),
        rocommands(roc),rostatus(rost),rodetails(rodt) {}
    watchStatus(const watchStatus& wscpy) : romemory(wscpy.romemory),roitpos(wscpy.roitpos),
        romemorySize(wscpy.romemorySize),rocodePointer(wscpy.rocodePointer),
        rocommands(wscpy.rocommands),rostatus(wscpy.rostatus),rodetails(wscpy.rodetails) {}
    const unsigned char *romemory;
    const unsigned char *roitpos;
    const size_t romemorySize=0;
    const std::vector<Instructer>::iterator rocodePointer;
    const std::vector<Instructer>& rocommands;
    const BFtext::ErrorType rostatus;
    const BFtext::ErrorContext rodetails;
};
class RunnerPointer
{
public:
    explicit RunnerPointer(int stksize,int codelen,size_t memsize):
        stackSize(stksize),codeLengthMaximum(codelen),
        memory(std::make_unique<unsigned char[]>(memsize)),sourceCode("") {
            itpos=memory.get();
            memorySize=memsize;
            status=BFtext::ErrorType::normal;
            std::memset(memory.get(),0,memsize);
        }
    explicit RunnerPointer(constructCFG cfg):
    RunnerPointer(cfg.stksize,cfg.codelen,cfg.memsize) {}
    class DebugPermission
    {
        DebugPermission()=default;
        friend class DebuggerRunPointer;
    };
    int singlestep();
    int singlestep(std::stringstream& iss,std::ostringstream& oss);
    int runAll();
    bool loadFile(const char *filePath,const char *progName);
    BFtext::ErrorType get_status() const
    { return status; }
    BFtext::ErrorContext get_stat_detail() const
    { return details; }
    watchStatus get_debugger_stat(DebugPermission) const
    {
        watchStatus ws(
            memory.get(),
            itpos,
            memorySize,
            codePointer,
            commands,
            status,
            details
        );
        return ws;
    }
private:
    int stackSize;
    int codeLengthMaximum;
    size_t memorySize;
    unsigned char *itpos;
    std::unique_ptr<unsigned char[]> memory;
    std::vector<Instructer>::iterator codePointer;
    std::stack<decltype(codePointer)> bucketStack;
    std::vector<Instructer> commands;
    std::string sourceCode;
    BFtext::ErrorType status;
    BFtext::ErrorContext details;
};
extern const int argMapSize;
extern const char *argKey[];
extern const char *argValue[];
extern std::map<const char*,int> argumentTable;
#endif