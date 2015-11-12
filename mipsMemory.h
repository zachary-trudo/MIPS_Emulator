// Author:          Zachary A Trudo
// Changelog:       Initial Creation - Nov 6, 2015
#ifndef __MIPSMEMORY_H__
#define __MIPSMEMORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "mipsInstructions.h"

#define DATA_MEM_SIZE 1028
#define INSTR_MEM_SIZE 1028
#define MAX_LABEL_SIZE
typedef struct mipsLabel
{
	char * label;
	int address;
}mipsLabel;

mipsLabel * labels[1024];

int getAddressFromLabel(char * LABEL);
int saveLabel(char * LABEL, int address);

void initMipsLabel(mipsLabel * labelStruct,  char* LABEL);

typedef struct instruction
{
    mipsLabel label;
    
    char*   LABEL;
    InstructionType instType;
    Instructions instr;

	char *rt;
	char *rs;
	char *rd;

	char* imm;

    char* addr;
}memInstruct;

void initMemInstruct(memInstruct* inst);
void copyInstructMem(memInstruct* const dest, memInstruct* const src);
void deleteMemInstruct(memInstruct* inst);
void deleteMemInstructOnStack(memInstruct* inst);

typedef struct dataMemory
{
    int* data;
    int size;
}dataMemory;

void initDataMemory(dataMemory* datMem);
void expandDataMemory(int* addr, int* size);
void deleteDataMemory(dataMemory* datMem);

void storeData(int* rt, int* rs, int* imm, int* dataSize, dataMemory* dataMem);
void loadData(int* rt, int* rs, int* imm, int* dataSize, dataMemory* dataMem);

int* getDataPointer(char* str, dataMemory* datMem);
int* getSize(dataMemory* datMem);
#endif
