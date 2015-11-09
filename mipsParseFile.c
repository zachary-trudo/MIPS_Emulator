#include "mipsParseFile.h"

regex_t instruction_re;


void init_parser_re(){
	//instruction re
	if(regcomp(&instruction_re, "[[:alnum:]]{3,5}", 0)){
		printf("Could not compile instruction_re - mipsParseFile.c");
		exit(1);
	}

	
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

/*
void parseFile(FILE* const infp, memInstruct* const instructMem, int* instructMemSize){
	FILE* fp = infp;
	memInstruct *memPtr = instructMem;

	while(!feof(fp)){
		while((read = getline(&line, &len, infp)) != -1){
			char * ins = 
		}
	}
	
}


*/
// Parse the file into instruction and data memory.
void parseFile(FILE* const infp, memInstruct* const instructMem, int* instructMemSize)
{
	printf("call to parseFile");
    FILE* fp = infp;
    memInstruct *memPtr = instructMem;

    memInstruct* curInstruct;
    char * line = NULL;
    size_t len  = 0;
    size_t read;
    
    char * token;
	char * label;

   // while(!feof(fp))
    //{
		printf("outer loop 1\n");
        while(!feof(fp) && (read = getline(&line, &len, infp)) != -1)
        {
		printf("loop 2\n");
            if (/*line != '#' && *line != '\n' &&*/ (int)strlen(line) > 1)
            {
				printf("Reading line from file:\n%s\n", line);
				//if(line[0] == '#' || line[0] == '\n'){
					//continue;
				//}
				

                // Create a new instruction.
               curInstruct = (memInstruct*) malloc(sizeof(memInstruct));
                curInstruct->instr = -1;
				curInstruct->rd = -1;
				curInstruct->rt = 0;
				curInstruct->rs = 0;
                // Replace all ',' with ' '
                replaceChar(line, ',', ' ');
				replaceChar(line, '\t', ' ');
				
                // Replace all '#' with '\0' - as thats the end of the line as far as our parser is concerned. 
                replaceChar(line, '#', '\0');
				
                // Grab first token.
                token = strtok(line, " ");

                // If we're not at the end of the line or the beginning of a comment parse.
                while(token && *token != '#' && *token != '\n')
                {
					//label = strtok(token, ":");
					//printf("parse label: %s \n", label);

					printf("parse token: %s \n", token);
					token = strcat(token, "\0");
					printf("token: %s\n", token);
					//no assigned instruction
                    if(curInstruct->instr == -1)
                    {
						//Program hangs in charToUpper. Need to append "\0".
                        curInstruct->instr = getInstructFromChar(token);
						printf("instruction: %d\n", curInstruct->instr);
                        if(curInstruct->instr == -1)
                        {
							printf("found a label %s\n", token);
                            strcpy(&curInstruct->LABEL, token);
                        }
                        else
                        {
                            curInstruct->instType = getInstructionType(curInstruct->instr);
                        }
                    }
                    else if(curInstruct->instType == RTYPE)
                    {
						printf("processing RTYPE instruction\n");
                       if(curInstruct->rd == -1)
                       {
							printf("token %s\n", token);
                           strcpy(&curInstruct->rd, token);
                       }
                       else if(!curInstruct->rs)
                       {
                           strcpy(&curInstruct->rs, token);
                       }
                       else
                       {
                           strcpy(&curInstruct->rt, token);
                           break;
                       }
                    }
                    else if (curInstruct->instType == ITYPE)
                    {
						printf("processing ITYPE instruction\n");
                        if(!curInstruct->rt)
                        {
                            strcpy(&curInstruct->rt, token);
                        }
                        else
                        {
                            if(containsChar(token, '('))
                            {
                                splitLoadToken(token, &curInstruct->imm, &curInstruct->rs);
                            }
                            else if(!curInstruct->rs)
                            {
                                strcpy(&curInstruct->rs, token);
                            }
                            else
                            {
                                strcpy(&curInstruct->imm, token);
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
                memPtr = curInstruct;
                memPtr++;
                instructMemSize++;
            }
			printf("bad line\n");
			if(feof(fp)){
				break;
			}
        }
   // }

    /*if (line)
    {
		printf("freeing line");
       // free(line);
    }
    if (token)
    {
		printf("freeing token");
       // free(token);
    }*/
	printf("returning from parsefile");
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

