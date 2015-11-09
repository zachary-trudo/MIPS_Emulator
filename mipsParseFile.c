#include <stdio.h>
#include <string.h>

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



// Parse the file into instruction and data memory.
void parseFile(FILE* infp, memInstruct *instructMem, int *datMem, mipsRegister *mipReg)
{
    memInstruct* curInstruct;

    char * line = NULL;
    size_t len  = 0;
    ssize_t read;
    
    char * tokendLine;

    while(infp != EOF)
    {
        while((read = getline(&line, &len, infp)) != -1)
        {
			//do we need to malloc? doens't declaring curInstruct reserve space for curInstruct?
            curInstruct = (memInstruct*) malloc(sizeof(memInstruct));
            if (*line != '#')
            {
                // Replace all ',' with ' '
                replaceChar(line, ',', ' ');
                // Grab token on ' '
                tokendLine = strtok(line, ' ');

                // If we're not at the end of the line parse.
                while(tokendLine)
                {
                    if (*tokendLine != '#')
                    {
                        if(!curInstruct->instr)
                        {
                            // getInstructFromChar will return NULL if tokenedLine isn't an instruction.
                            curInstruct->instr = getInstructFromChar(tokendLine);
                            if (!curInstruct->instr)
                            {
                                strcpy(curInstruct->label.label, tokendLine);
                            }
                        }
                        else if (*tokendLine == '$' || (*tokendLine >= '0' && *tokendLine <= '9'))
                        {
                            if(!curInstruct->rd)
                            {
                                strcpy(curInstruct->rd, tokendLine);
                            }
						}
					}
                }
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
void writeFile(FILE* outfp, memInstruct *instructMem, int *dataMem){
}




