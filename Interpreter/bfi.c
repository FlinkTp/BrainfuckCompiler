#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int defaultCodeLengthMaximum=100000;
const int defaultRuntimeMemory=100000;
const int defaultStackSize=100000;
int main(int argc,char *argv[],char **envp)
{
    if(argc<=1)
    {
        puts("Usage: bfi <FILE>");
        return 1;
    }
    FILE *fp=fopen(argv[1],"r+");
    if(fp==NULL)
    {
        printf("%s: Cannot open %s",argv[0],argv[1]);
        return 1;
    }
    char *input=(char *)calloc(defaultCodeLengthMaximum,sizeof(char));
    char *code=(char *)calloc(defaultCodeLengthMaximum,sizeof(char));
    char *codeBegin=code;
    while(~fscanf(fp,"%s",input))
        strcat(code,input);
    int codePointer=0,memoryPointer=0,stackPointer=-1;
    unsigned char *MEMORY=(unsigned char *)calloc(defaultRuntimeMemory,sizeof(unsigned char));
    unsigned char *pointerCurrent=MEMORY;
    int *STACK=(int *)calloc(defaultStackSize,sizeof(int));
    while(*code!='\0'&&memoryPointer>=0)
    {
        switch(*code)
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
                if(stackPointer>=defaultStackSize)
                {
                    puts("");
                    puts("[FATAL] Segment Fault: Stack overflow!");
                    exit(1);
                }
                *STACK=codePointer;
                STACK++;
                break;
            case ']':
                if(stackPointer==-1)
                {
                    puts("");
                    puts("[FATAL] a \']\' cannot match \'[\'!");
                    exit(1);
                }
                stackPointer--;
                STACK--;
                if(*pointerCurrent)
                {
                    codePointer=(*STACK)-1;
                    code=codeBegin+codePointer;
                }
                break;
        }
        code++;
        codePointer++;
    }
    if(memoryPointer==-1)
        puts("Program terminated with exit code 0.");
    else
        printf("Program terminated with exit code %d.\n",*pointerCurrent);
    return 0;
}