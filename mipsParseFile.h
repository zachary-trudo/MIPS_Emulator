#ifndef __MIPSLOADFILE_H__
#define __MIPSLOADFILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mipsInstructions.h"
#include "mipsMemory.h"

void stripLeadingWhiteSpace(char* str);
void replaceChar(char* str, char garbage, char replace);
int containsChar(char* const str, char item);
void splitLoadToken(char* token, char* const imm, char* const rs);

// Parse the file into instruction and data memory.
void parseFile(FILE* const infp, memInstruct* const instructMem, int* instructMemSize);

// For debugging... Write out what we thought we got into a file. 
void writeFile(FILE* outfp, memInstruct* const instructMem, const int instructMemSize);



#endif
