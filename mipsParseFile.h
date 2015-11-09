#ifndef __MIPSLOADFILE_H__
#define __MIPSLOADFILE_H__

#include "mipsInstructions.h"
#include "mipsMemory.h"

void replaceChar(char* str, char garbage, char replace);
int containsChar(const char* str, char item);
void splitLoadToken(char* token, const char* imm, const char* rs);
// Parse the file into instruction and data memory.
void parseFile(const FILE* infp, const instructionMemory *instructMem);

// For debugging... Write out what we thought we got into a file. 
void writeFile(FILE* outfp, instructionMemory *instructMem, dataMemory *dataMem);



#endif
