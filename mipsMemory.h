// Author:          Zachary A Trudo
// Changelog:       Initial Creation - Nov 6, 2015
#ifndef __MIPSMEMORY_H__
#define __MIPSMEMORY_H__

#include "mipsInstructions.h"

#define DATA_MEM_SIZE 1028
#define INSTR_MEM_SIZE 20560

typedef struct mipsLabel
{
	char * label;
	int address;
}mipsLabel;

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


extern int data_mem[DATA_MEM_SIZE];
extern memInstruct instr_mem[INSTR_MEM_SIZE];

void save_data(int address, int value);
int load_data(int address);

void save_program(const memInstruct* program);
memInstruct fetch_instr(int address);
#endif
