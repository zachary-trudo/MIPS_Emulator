#ifndef __MIPSMEMORY_H__
#define __MIPSMEMORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "mipsInstructions.h"

#define DATA_MEM_SIZE 1028
#define INSTR_MEM_SIZE 1028
#define MAX_LABEL_SIZE
typedef struct instruction
{
    char*   LABEL;
    InstructionType instType;
    Instructions instr;

	char *rt;
	char *rs;
	char *rd;

	char* imm;

    char* addr;
}memInstruct;

int getAddressFromLabel(char * LABEL, const memInstruct* instructs, int numInstructs);
void initMemInstruct(memInstruct* inst);
void copyInstructMem(memInstruct* const dest, memInstruct* const src);
void deleteMemInstruct(memInstruct* inst);
void deleteMemInstructOnStack(memInstruct* inst);

typedef struct dataMemory
{
    int* data;
    int size;
    int* used;
}dataMemory;

void initDataMemory(dataMemory* datMem, int initSize);
void expandDataMemory(dataMemory* oldDataMemory, int* size);
void deleteDataMemory(dataMemory* datMem);

void storeData(int* rt, int* ALU_RESULT, int* dataSize, dataMemory* dataMem);
void loadData(int* MEM_ALU_RESULT, int* ALU_RESULT, int* dataSize, dataMemory* dataMem);

int* getDataPointer(char* str, dataMemory* datMem);
int* getSize(dataMemory* datMem);

#endif
