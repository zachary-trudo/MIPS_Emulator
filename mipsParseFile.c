#include <stdio.h>
#include <string.h>

#include "mipsParseFile.h"
#include "mipsInstruction.h"
#include "mipsRegisters.h"

// Parse the file into instruction and data memory.
void parseFile(FILE* infp, instructionMemory *instructMem, dataMemory *datMem, mipsRegisters *mipReg)
{
    char * line = NULL;
    size_t len  = 0;
    ssize_t read;
    
    char * tokenedLine;

    while(infp != EOF)
    {
        while((read = getline(&line, &len, infp)) != -1)
        {
            tokenedLine

        }
    }

    if (line)
    {
        free(line)
    }
    return;
}

// For debugging... Write out what we thought we got into a file. 
void writeFile(FILE* outfp, instructionMemory *instructMem, dataMemory *dataMem);



#endif
