#ifndef _BFCONFIG_
#define _BFCONFIG_
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <memory>
#include "bftext.hpp"
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
        rowNumber(row),colNumber(col),operate(op),jump_to(next) {}
    char get_operate() const
    { return operate; }
    int get_row() const
    { return rowNumber; }
    int get_col() const
    { return colNumber; }
    Instructer *get_next() const
    { return jump_to; }
private:
    int rowNumber;
    int colNumber;
    char operate;
    Instructer *jump_to;
};
class RunnerPointer
{
public:
    explicit RunnerPointer(int stksize,int codelen,size_t memsize):
        stackSize(stksize),codeLengthMaximum(codelen),
        memory(std::make_unique<unsigned char[]>(memsize)) {
            itpos=memory.get();
            memorySize=memsize;
            status=BFtext::ErrorType::normal;
        }
    explicit RunnerPointer(constructCFG cfg):
    RunnerPointer(cfg.stksize,cfg.codelen,cfg.memsize) {}
    int singlestep();
    int runAll();
    void loadFile(const char *filePath,const char *progName);
    BFtext::ErrorType get_status() const
    { return status; }
    BFtext::ErrorContext get_stat_detail() const
    { return details; }
private:
    int stackSize;
    int codeLengthMaximum;
    size_t memorySize;
    unsigned char *itpos;
    std::unique_ptr<unsigned char[]> memory;
    std::vector<Instructer>::iterator codePointer;
    std::stack<decltype(codePointer)> bucketStack;
    std::vector<Instructer> commands;
    BFtext::ErrorType status;
    BFtext::ErrorContext details;
};
const int argMapSize=4;
const char *argKey[]={"-m","-s","-l","-c"};
const char *argValue[]={"--memory","--stack","--line","--code"};
#endif