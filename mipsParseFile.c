#include "mipsParseFile.h"



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

void splitLoadToken(char* token, char* const imm, char* const rs)
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

// Parse the file into instruction and data memory.
void parseFile(FILE* const infp, memInstruct* const instructMem, int* instructMemSize)

{
    FILE* fp = infp;
    memInstruct *memPtr = instr_mem;
	int j = 0;
    memInstruct* curInstruct;
    char * line = NULL;
    size_t len  = 0;
    size_t read;
    
    char * token;
	char * label;

        while(!feof(infp) && (read = getline(&line, &len, infp)) != -1)
        {

            if ((int)strlen(line) > 1)

            {


				curInstruct = init_memInstruct();
                // Replace all ',' with ' '
                replaceChar(line, ',', ' ');
				replaceChar(line, '\t', ' ');
				//replaceChar(line, '#', '\0');
                // Grab first token.
                token = strtok(line, " ");

                // If we're not at the end of the line or the beginning of a comment parse.
                while(token && token[0] != '#' && *token != '\n')
                {
                    if(curInstruct->instr == -1)
                    {

                        curInstruct->instr = getInstructFromChar(token);
                        if(curInstruct->instr == -1)
                        {
                            strcpy(&curInstruct->LABEL, token);
                        }
                        else
                        {
							j++;
                            curInstruct->instType = getInstructionType(curInstruct->instr);

                        }
                    }
                    else if(curInstruct->instType == RTYPE)
                    {
                       if(!strlen(&curInstruct->rd))
                       {
                           strcpy(&curInstruct->rd, token);
                       }
                       else if(!strlen(&curInstruct->rs))
                       {
                           strcpy(&curInstruct->rs, token);
                       }
                       else
                       {
						   replaceChar(token, '\n', '\0');
                           strcpy(&curInstruct->rt, token);
                           break;
                       }
                    }
                    else if (curInstruct->instType == ITYPE)
                    {
                        if(!strlen(&curInstruct->rt))
                        {
                            strcpy(&curInstruct->rt, token);
                        }
                        else
                        {

                            if(containsChar(token, '('))
                            {
                                splitLoadToken(token, &curInstruct->imm, &curInstruct->rs);
                            }
                            else if(!strlen(&curInstruct->rs))
                            {
                                strcpy(&curInstruct->rs, token);
                            }
                            else
                            {
								
								replaceChar(token, '\n', '\0');
								if(isalpha(token[0])){
									//Assuming mips labels cannot start with a digit, need to look into this
									strcpy(&curInstruct->LABEL, token);
								}else{
                                	strcpy(&curInstruct->imm, token);
								}
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(curInstruct->instr == J || curInstruct->instr == JAL)
                        {
                            strcpy(&curInstruct->addr, token);
                            break;
                        }
                        else
                        {
                            strcpy(&curInstruct->rs, token);
                        }
                    }

                    token = strtok(NULL, " ");
                }

					if(curInstruct->instr != -1){
						save_instr(curInstruct, j-1);
					}
                memPtr++;


                instructMemSize++;
				
				free(curInstruct);
            }
        }


        free(line);

    return;
}
// For debugging... Write out what we thought we got into a file. 

void writeFile(FILE* const outfp, memInstruct* const instructMem, const int instructMemSize)
{
    FILE* fp = outfp;
    memInstruct *memPtr = instructMem;
    int i = 0;


    for(i; i < instructMemSize; i++)
    {
        fprintf(outfp, "\n");
        printf("\n");
        if(memPtr->instType)
            fprintf(outfp, "type: %s ", instructTypes[memPtr->instType]);
            printf("type: %s ", instructTypes[memPtr->instType]);
        if(memPtr->LABEL)
            fprintf(outfp, "LABEL: %s ", memPtr->LABEL);
            printf("LABEL: %s ", memPtr->LABEL);
        if(memPtr->instr)
            fprintf(outfp, "instr: %s ", instructNames[memPtr->instr]);
            printf("instr: %s ", instructNames[memPtr->instr]);
        if(memPtr->rs)
            fprintf(outfp, "rs: %s ", memPtr->rs);
            printf("rs: %s ", memPtr->rs);
        if(memPtr->rt)
            fprintf(outfp, "rt: %s ", memPtr->rt);
            printf("rt: %s ", memPtr->rt);
        if(memPtr->rd)
            fprintf(outfp, "rd: %s ", memPtr->rd);
            printf("rd: %s ", memPtr->rd);
        if(memPtr->imm)
            fprintf(outfp, "imm: %s ", memPtr->imm);
            printf("imm: %s ", memPtr->imm);
        if(memPtr->addr)
            fprintf(outfp, "addr: %s.", memPtr->addr);
            printf("addr: %s.", memPtr->addr);
        memPtr++;
    }
}

