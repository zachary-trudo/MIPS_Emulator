// Author:          Zachary A Trudo
// Changelog:       Initial Creation - Nov 6, 2015
#ifndef __MIPSMEMORY_H__
#define __MIPSMEMORY_H__

#include "mipsInstructions.h"

#define DATA_MEM_SIZE 1028
#define INSTR_MEM_SIZE 20560
#define REG_NAME_SIZE 7
#define IMM_NAME_SIZE 10
#define LABEL_SIZE 10
typedef struct mipsLabel
{
	char * label;
	int address;
}mipsLabel;

typedef struct instruction
{
    mipsLabel label;
    
    char   LABEL[LABEL_SIZE];
    InstructionType instType;
    Instructions instr;

	char rt[REG_NAME_SIZE];
	char rs[REG_NAME_SIZE];
	char rd[REG_NAME_SIZE];

	char imm[IMM_NAME_SIZE];

    char* addr[IMM_NAME_SIZE];
}memInstruct;


extern int data_mem[DATA_MEM_SIZE];
extern memInstruct instr_mem[INSTR_MEM_SIZE];

//must call free on returned memInstruct
memInstruct * init_memInstruct();

void copy_memInstr(memInstruct* destInstr, memInstruct* srcInstr);
void save_data(int address, int value);
int load_data(int address);

void save_program(const memInstruct* program);
void save_instr(memInstruct* instr, int line);
memInstruct fetch_instr(int address);
#endif
