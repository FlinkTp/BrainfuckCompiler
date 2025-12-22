#include "bfconfig.hpp"
#include "bftext.hpp"
#include <map>
namespace BFtext
{
    const std::string VERSION="v0.1.0-beta";
    const ErrorContext null_content;
    const std::string fileError=": Cannot open ";
    const std::string memoryOverflow="[FATAL] memory OVERFLOW!";
    const std::string stackOverflow="[FATAL] Segment Fault: Stack OVERFLOW!";
    const std::string bucketCannotMatch="[FATAL] Preprocessor: brackets cannot match!";
    const std::string errorTitle="!====================================!";
    const std::string usagePrompt=
    "usage: bfi <FILE> [-m <value> | --memory <value>]\n"
    "                  [-c <value> | --code <value>]\n"
    "                  [-s <value> | --stack <value>]\n";
//  "                  [-l <value> | --line <value>]";
    const std::string exitTitle="-----------------------------------------------------------";
    const std::string exitMessage="Brainfuck Program successfully Terminated! Exitcode = ";
    const std::string *errMessage[]={&fileError,&usagePrompt,&memoryOverflow,
        &stackOverflow,&bucketCannotMatch};
    const std::string debugPrompt="BFdbg >>> ";
    const std::string debugUsage=
    "usage: bfdbg <FILE> [-m <value> | --memory <value>]\n"
    "                    [-c <value> | --code <value>]\n"
    "                    [-s <value> | --stack <value>]\n";
//  "                    [-l <value> | --line <value>]";
    const std::string debugHelp=
    "List of commands:\n\n"
    "help - get help from this page\n"
    "[bp | b] <ip> - set breakpoint at ip\n"
    "[step | s] - run a single step (an instruction)\n"
    "[next | n] - run a single step (without showing status)\n"
    "[stat | a] - show status of current runner\n"
    "[continue | x | c] - run until meet a breakpoint or an exception\n"
    "[watch | w] <mp> - watch a memory cell\n"
    "[debp | db] <id> - remove a breakpoint with id\n"
    "[dewatch | dw] <id> - remove a watch with id\n"
    "[setinput | si] - set input (use EOF to end input)\n"
    "[watchoutput | wo] - watch user screen to see output\n"
    "[exit | quit] - exit the debugging program";
}
/*
std::map<const char*,int> argumentTable={
    {"-m",0},{"--memory",0},
    {"-s",1},{"--stack",1},
    {"-c",3},{"--code",3}
};
*/
const int argMapSize=4;
const char *argKey[]={"-m","-s","-l","-c"};
const char *argValue[]={"--memory","--stack","--line","--code"};