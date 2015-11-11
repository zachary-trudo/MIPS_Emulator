#include "mipsParseFile.h"

void stripLeadingWhiteSpace(char *str)
{
    char *beg = str;

    while(isspace(*str))
    {
        str++;
    }

    while(*str)
    {
        *beg = *str;
        beg++;
        str++;
    }
    *beg = '\0';
}

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

int containsChar(char* const str, char item)
{
    int returnVal = 0;
    char* strPtr = str;

    for(strPtr; *strPtr != '\0'; strPtr++)
    {
        if(*strPtr == item)
        {
            returnVal = 1;
            break;
        }
    }
    return returnVal;
}

void splitLoadToken(char* token, char* imm, char* rs)
{
    char* immPtr = imm;
    char* rsPtr = rs;

    for(token; *token != '('; token++)
    {
        *immPtr = *token;
        immPtr++;
    }
    *immPtr = '\0';
    token++;

    for(token; *token != ')'; token++)
    {
        *rsPtr = *token;
        rsPtr++;
    }
    *rsPtr = '\0';
}

int numberOfWords(char* str)
{
    char* strPtr = str;
    int inWord = 0;
    int numWords = 0;   

    do switch(*strPtr)
    {
        case '\0':
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            if (inWord) 
            {
                inWord = 0;
                numWords++;
            }
            break;
        default:
            inWord = 1;
    } while(*strPtr++);
    return numWords;
}


// Parse the file into instruction and data memory.
void parseFile(FILE* infp, memInstruct* const instructMem, int* instructMemSize)
{
    memInstruct *memPtr = &(instructMem[0]);

    memInstruct* curInstruct;
    char * line = NULL;
    size_t len  = 0;
    size_t read;
    
    char * token;

    int numWords = 0;

    while(!feof(infp))
    {
        while((read = getline(&line, &len, infp)) != -1)
        {
            if (*line != '#' && *line != '\n')
            {
                // Create a new instruction.
                curInstruct = (memInstruct*) malloc(sizeof(memInstruct));
                initMemInstruct(curInstruct);

                // Remove Leading WhiteSpace
                if(isspace(*line))
                    stripLeadingWhiteSpace(line);
                // Replace all ',' with ' '
                replaceChar(line, ',', ' ');
                // Replace all '#' with '\0' - as thats the end of the line as far as our parser is concerned. 
                replaceChar(line, '#', '\0');
                // Replace all '\n' with ' '
                replaceChar(line, '\n', ' ');
                // Replace all ':' with ' '
                replaceChar(line, ':', ' ');

                // Grab first token.
                numWords = numberOfWords(line);
                token = strtok(line, " ");

                // If we're not at the end of the line or the beginning of a comment parse.
                while(token && *token != '#')
                {
                    if(numWords == 1)
                    {
                        curInstruct->LABEL = (char*) malloc(sizeof(token));
                        charToUpper(token);
                        strcpy(curInstruct->LABEL, token);
                    }
                    else if(curInstruct->instr == NONE)
                    {
                        curInstruct->instr = getInstructFromChar(token);
                        if(curInstruct->instr == NONE)
                        {
                            curInstruct->LABEL = (char*) malloc(sizeof(token));
                            strcpy(curInstruct->LABEL, token);
                        }
                        else
                        {
                            curInstruct->instType = getInstructionType(curInstruct->instr);
                        }
                    }
                    else if(curInstruct->instType == RTYPE)
                    {
                       if(!curInstruct->rd)
                       {
                           curInstruct->rd = (char*) malloc(sizeof(token));
                           strcpy(curInstruct->rd, token);
                       }
                       else if(!curInstruct->rs)
                       {
                           curInstruct->rs = (char*) malloc(sizeof(token));
                           strcpy(curInstruct->rs, token);
                       }
                       else
                       {
                           curInstruct->rt = (char*) malloc(sizeof(token));
                           strcpy(curInstruct->rt, token);
                           break;
                       }
                    }
                    else if (curInstruct->instType == ITYPE)
                    {
                        if(!curInstruct->rt)
                        {
                            curInstruct->rt = (char*) malloc(sizeof(token));
                            strcpy(curInstruct->rt, token);
                        }
                        else
                        {
                            if(containsChar(token, '('))
                            {
                                curInstruct->imm = (char*) malloc(sizeof(char) * 4);
                                curInstruct->rs  = (char*) malloc(sizeof(char) * 4);
                                splitLoadToken(token, curInstruct->imm, curInstruct->rs);
                            }
                            else if(!curInstruct->rs)
                            {
                                curInstruct->rs = (char*) malloc(sizeof(token));
                                strcpy(curInstruct->rs, token);
                            }
                            else if(curInstruct->instr == BEQ || curInstruct->instr == BNE)
                            {
                                curInstruct->addr = (char*) malloc(sizeof(token));
                                strcpy(curInstruct->addr, token);
                                break;
                            }
                            else
                            {
                                curInstruct->imm = (char*) malloc(sizeof(token));
                                strcpy(curInstruct->imm, token);
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(curInstruct->instr == J || curInstruct->instr == JAL)
                        {
                            curInstruct->addr = (char*) malloc(sizeof(token));
                            strcpy(curInstruct->addr, token);
                            break;
                        }
                        else
                        {
                            curInstruct->rs = (char*) malloc(sizeof(token));
                            strcpy(curInstruct->rs, token);
                            break;
                        }
                    }

                    token = strtok(NULL, " ");
                }
                copyInstructMem(memPtr, curInstruct);
                memPtr++;
                deleteMemInstruct(curInstruct);
                (*instructMemSize)++;
            }
        }
    }

    if (line)
    {
        free(line);
    }
    return;
}

// For debugging... Write out what we thought we got into a file. 
void writeFile(FILE* const outfp, memInstruct* const instructMem, const int instructMemSize)
{
    memInstruct *memPtr = instructMem;
    int i = 0;

    for(i; i < instructMemSize; i++)
    {
        fprintf(outfp, "\n");
        printf(" \n ");
        fprintf(outfp, "LABEL: %s ", (char*) memPtr->LABEL);
        printf("LABEL: %s ", memPtr->LABEL);
        if(memPtr->instr >= 0)
        {
            fprintf(outfp, "type: %s ", (char*) instructTypes[memPtr->instType]);
            printf("type: %s ", instructTypes[memPtr->instType]);
            
            fprintf(outfp, "instr: %s ", (char*) instructNames[memPtr->instr]);
            printf("instr: %s ", instructNames[memPtr->instr]);
            
            fprintf(outfp, "rs: %s ", memPtr->rs);
            printf("rs: %s ", memPtr->rs);
            
            fprintf(outfp, "rt: %s ", memPtr->rt);
            printf("rt: %s ", memPtr->rt);
            
            fprintf(outfp, "rd: %s ", memPtr->rd);
            printf("rd: %s ", memPtr->rd);
            
            fprintf(outfp, "imm: %s ", memPtr->imm);
            printf("imm: %s ", memPtr->imm);
            
            fprintf(outfp, "addr: %s.", memPtr->addr);
            printf("addr: %s.", memPtr->addr);
        }
        memPtr++;
    }
}

