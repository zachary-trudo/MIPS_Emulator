#ifndef __MIPSLOADFILE_H__
#define __MIPSLOADFILE_H__

#include "mipsInstructions.h"
#include "mipsMemory.h"
#include "mipsRegisters.h"

// Parse the file into instruction and data memory.
void parseFile(FILE* infp, memInstruct *instructMem, int *datMem, mipsRegister *mipReg);

// For debugging... Write out what we thought we got into a file. 
void writeFile(FILE* outfp, memInstruct *instructMem, int *dataMem);



#endif
