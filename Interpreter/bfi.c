#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int defaultCodeLengthMaximum=100000;
const int defaultRuntimeMemory=100000;
const int defaultStackSize=100000;
const int argMapSize=4;
const char *argKey[]={"-m","-s","-l","-c"};
const char *argValue[]={"--memory","--stack","--line","--code"};
typedef struct
{
    int RuntimeMemory;
    int Stacksize;
}RuntimeConfig;
typedef struct
{
    int codeLengthMaximum;
    int lineLengthMaximum;
}StaticConfig;
RuntimeConfig cfg;
StaticConfig cfgStatic;
int codeRunner(char *Code)
{
    int codePointer=0,memoryPointer=0,stackPointer=-1;
    char *codeBegin=Code;
    unsigned char *MEMORY=(unsigned char *)calloc(cfg.RuntimeMemory,sizeof(unsigned char));
    unsigned char *pointerCurrent=MEMORY;
    int *STACK=(int *)calloc(cfg.Stacksize,sizeof(int));
    while(*Code!='\0'&&memoryPointer>=0)
    {
        if(memoryPointer>cfg.RuntimeMemory)
            return -1;
        switch(*Code)
        {
            case '+':
                (*pointerCurrent)++;
                break;
            case '-':
                (*pointerCurrent)--;
                break;
            case '>':
                ++pointerCurrent;
                memoryPointer++;
                break;
            case '<':
                --pointerCurrent;
                memoryPointer--;
                break;
            case ',':
                *pointerCurrent=getchar();
                break;
            case '.':
                putchar(*pointerCurrent);
                break;
            case '[':
                stackPointer++;
                if(stackPointer>=cfg.Stacksize)
                    return -2;
                *STACK=codePointer;
                STACK++;
                break;
            case ']':
                if(stackPointer==-1)
                    return -3;
                stackPointer--;
                STACK--;
                if(*pointerCurrent)
                {
                    codePointer=(*STACK)-1;
                    Code=codeBegin+codePointer;
                }
                break;
        }
        Code++;
        codePointer++;
    }
    if(memoryPointer==-1)
        return 0;
    else
        return *pointerCurrent;
    free(STACK);
    free(MEMORY);
}
void retcodeHandling(int retCode)
{
    switch(retCode)
    {
        case -1:
            puts("\n!====================================!");
            puts("[FATAL] memory OVERFLOW!");
            break;
        case -2:
            puts("\n!====================================!");
            puts("[FATAL] Segment Fault: Stack OVERFLOW!");
            break;
        case -3:
            puts("\n!====================================!");
            puts("[FATAL] a \']\' cannot match \'[\'!");
            break;
        default:
            printf("\n--------------------------------------\nProgram terminated with exit code %d.\n",retCode);
    }
}
void usage()  
{
    puts("usage: bfi <FILE> [-m <value> | --memory <value>]");
    puts("                  [-c <value> | --code <value>]");
    puts("                  [-s <value> | --stack <value>]");
    puts("                  [-l <value> | --line <value>]");
    exit(1);
}
int main(int argc,char *argv[],char **envp)
{
    cfg=(RuntimeConfig){.RuntimeMemory=defaultRuntimeMemory,.Stacksize=defaultStackSize};
    cfgStatic=(StaticConfig){.codeLengthMaximum=defaultCodeLengthMaximum,.lineLengthMaximum=defaultCodeLengthMaximum};
    if(argc<=1)
        usage();
    FILE *fp=fopen(argv[1],"r");
    if(fp==NULL)
    {
        printf("%s: Cannot open %s",argv[0],argv[1]);
        return 1;
    }
    char *input=(char *)calloc(cfgStatic.codeLengthMaximum,sizeof(char));
    char *code=(char *)calloc(cfgStatic.lineLengthMaximum,sizeof(char));
    while(~fscanf(fp,"%s",input))
        strcat(code,input);
    int runCodeReturn;
    runCodeReturn=codeRunner(code);
    retcodeHandling(runCodeReturn);
    free(input);
    free(code);
    fclose(fp);
    return 0;
}