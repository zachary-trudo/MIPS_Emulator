#ifndef __MIPSLOADFILE_H__
#define __MIPSLOADFILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mipsInstructions.h"
#include "mipsMemory.h"

// This function skips all leading whitespace, and then copies the rest of the original string 
// back into the beginning and places a '\0' character at the end.
void stripLeadingWhiteSpace(char* str);

// This function will replace all chars matching 'garbage' in a string.
void replaceChar(char* str, char garbage, char replace);

// Returns 1 if 'item' is found in 'str'
int containsChar(char* const str, char item);

// Very specific function for parsing memory addresses. 
// Splits on the '(' symbol and cuts it into the imm and the rs.
void splitLoadToken(char* token, char* const imm, char* const rs);

// Counts up all the words in a string.
int numberOfWords(char* str);


// Parse the file into instruction and data memory.
void parseFile(FILE* const infp, memInstruct* const instructMem, int* instructMemSize);

// For debugging... Write out what we thought we got into a file. 
void writeFile(FILE* outfp, memInstruct* const instructMem, const int instructMemSize);



#endif
