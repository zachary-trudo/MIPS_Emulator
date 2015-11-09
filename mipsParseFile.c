#include <stdio.h>
#include <string.h>

#include "mipsParseFile.h"
#include "mipsInstruction.h"
#include "mipsRegisters.h"

void replaceChar(char *str, char garbage, char replace)
{
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++)
    {
        *dst = *src;
        if (*dst == garbage)
        {
            *dst = replace;
        }
        *dst++;
    }
    *dst = '\0';
}

int containsChar(const char* str, char item)
{
    int returnVal = 0;
    char* strPtr = str;

    for(strPtr; str != '\0'; str++)
    {
        if(*str == item)
        {
            returnVal = 1;
            break;
        }
    }
    return returnVal;
}

void splitLoadToken(char* token, const char* imm, const char* rs)
{
    char* immPtr = imm;
    char* rsPtr = rs;

    for(token; token != '('; token++)
    {
        *immPtr = *token;
        immPtr++;
    }
    *immPtr = '\0';
    token++;

    for(token; token != ')'; token++)
    {
        *rsPtr = *token;
        rsPtr++;
    }
    *rsPtr = '\0';
}


// Parse the file into instruction and data memory.
void parseFile(const FILE* infp, const instructionMemory *instructMem, int* instructMemSize)
{
    FILE* fp = infp;
    instructionMemory *memPtr = instructMem;

    memInstruct* curInstruct;
    char * line = NULL;
    size_t len  = 0;
    ssize_t read;
    
    char * token;

    while(infp != EOF)
    {
        while((read = getline(&line, &len, infp)) != -1)
        {
            if (*line != '#')
            {
                // Create a new instruction.
                curInstruct = (memInstruct*) malloc(sizeof(meminstruct));
                curInstruct.instr = NULL;

                // Replace all ',' with ' '
                replaceChar(line, ',', ' ');
                // Replace all '#' with '\0' - as thats the end of the line as far as our parser is concerned. 
                replaceChar(line, '#', '\0');

                // Grab first token.
                token = strtok(line, ' ');

                // If we're not at the end of the line or the beginning of a comment parse.
                while(token && token != '#')
                {
                    if(!curInstruct.instr)
                    {
                        curInstruct.instr = getInstructFromChar(token);
                        if(!curInstruct.instr)
                        {
                            strcpy(curInstruct.LABEL, token);
                        }
                        else
                        {
                            curInstruct.instuctType = getInstructionType(curInstruct.instr);
                        }
                    }
                    else if(curInstruct.type == RTYPE)
                    {
                       if(!curInstruct.rd)
                       {
                           strcpy(curInstruct.rd, token);
                       }
                       else if(!curInstruct.rs)
                       {
                           strcpy(curInstruct.rs, token);
                       }
                       else
                       {
                           strcpy(curInstruct.rt, token);
                           break;
                       }
                    }
                    else if (curInstruct.type == ITYPE)
                    {
                        if(!curInstruct.rt)
                        {
                            strcpy(curInstruct.rt, token);
                        }
                        else
                        {
                            if(containsChar(token, '('))
                            {
                                splitLoadToken(token, &curInstruct.imm, &curInstruct.rs);
                            }
                            else if(!curInstruct.rs)
                            {
                                strcpy(curInstruct.rs, token);
                            }
                            else
                            {
                                strcpy(curInstruct.imm, token);
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(curInstruct.instr == J || curInstruct.instr == JAL)
                        {
                            strcpy(curInstruct.addr, token);
                            break;
                        }
                        else
                        {
                            strcpy(curInstruct.rs, token);
                        }
                    }

                    token = strtok(NULL, ' ');
                }
                *memPtr = curInstruct;
                memPtr++;
                instructMemSize++;
            }
        }
    }

    if (line)
    {
        free(line);
    }
    if (token)
    {
        free(token);
    }
    return;
}

// For debugging... Write out what we thought we got into a file. 
void writeFile(const FILE* outfp, const instructionMemory *instructMem, int* instructMemSize)
{
    FILE* fp = outfp;
    instructionMemory *memPtr = instructMem;
    int i = 0;

    for(i; i < instructMemSize; i++)
    {
        fprintf("\n");
        if(memPtr.type)
            fprintf("type: %s ", memPtr.type);
            printf("type: %s ", memPtr.type);
        if(memPtr.LABEL)
            fprintf("LABEL: %s ", memPtr.LABEL);
            printf("LABEL: %s ", memPtr.LABEL);
        if(memPtr.instr)
            fprintf("instr: %s ", memPtr.instr);
            printf("instr: %s ", memPtr.instr);
        if(memPtr.rs)
            fprint("rs: %s ", memPtr.rs);
            print("rs: %s ", memPtr.rs);
        if(memPtr.rt)
            fprintf("rt: %s ", memPtr.rt);
            printf("rt: %s ", memPtr.rt);
        if(memPtr.rd)
            fprinttf("rd: %s ", memPtr.rd);
            printtf("rd: %s ", memPtr.rd);
        if(memPtr.imm)
            fprintf("imm: %s ", memPtr.imm);
            printf("imm: %s ", memPtr.imm);
        if(memPtr.addr)
            fprintf("addr: %s.", memPtr.addr);
            printf("addr: %s.", memPtr.addr);
        memPtr++;
    }
}







#endif
