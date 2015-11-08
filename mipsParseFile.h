#ifndef __MIPSLOADFILE_H__
#define __MIPSLOADFILE_H__

#include "mipsInstructions.h"
#include "mipsMemory.h"

// Parse the file into instruction and data memory.
void parseFile(FILE* infp, instructionMemory *instructMem, dataMemory *datMem);

// For debugging... Write out what we thought we got into a file. 
void writeFile(FILE* outfp, instructionMemory *instructMem, dataMemory *dataMem);



#endif
