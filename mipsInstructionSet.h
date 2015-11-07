// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#ifndef __MIPSINSTRUCTIONSET_H__
#define __MIPSINSTRUCTIONSET_H__
#include <stdlib.h>
#include <stdio.h>
#include "mipsRegisters.h" // Contains the mipsRegister struct.
#include "mipsMemory.h"

typedef enum instructs  {ADD, ADDI, ADDU, ADDIU, SUB, SUBI, SUBU, SUBIU, AND, OR, BEQ, BGTZ, BLTZ, BNE, J, LW} Instructions;

const char* instructNames[] = {"ADD", "ADDI", "ADDU", "ADDIU", "SUB", "SUBI", "SUBU", "SUBIU", "AND", "OR", "BEQ", "BGTZ", "BLTZ", "BNE", "J", "LW"};


// ALU
int MIPS_ALU(const int rs, const int rt, int *overflow, const Instructions instruction);

// Arithmetic Operations - Basic arithmetic operations
int MIPS_ADD(const int rs, const int rt, int *overflow);
int MIPS_ADDI(const int rs, const int immediate, int *overflow);
int MIPS_ADDU(const int rs, const int rt);
int MIPS_ADDIU(const int rs, const int rt);

int MIPS_SUB(const int rs, const int rt, int *overflow);
int MIPS_SUBI(const int rs, const int immediate, int *overflow);
int MIPS_SUBU(const int rs, const int rt);
int MIPS_SUBIU(const int rs, int immediate);

// Logical Operations
int MIPS_AND(const int rs, const int rt);
int MIPS_OR(const int rs, const int rt);

// Branch Operations - Should make basic comparison, and then pass the jump to (MIPS_J) if we really need to jump. 
int MIPS_BEQ(int *stored, int *temporary, char *LABEL, int *nextInstruction);
int MIPS_BGTZ(int *stored, char *LABEL, int *nextInstruction);
int MIPS_BLTZ(int *stored, char *LABEL, int *nextInstruction);
int MIPS_BNE(int *stored, char *LABEL, int *nextInstruction);

// Jump Operations - I think we should have a "Next Instruction" global. This could just change where it is pointing to. 
int MIPS_J(char *LABEL, int *nextInstruction);

// Load Operations
int MIPS_LW(int *temporary, memoryAddress *location); 

// TODO: There are actually a lot of commands I haven't included we'll need to flesh out all of them most likely. -Zach 6 Nov 2015

#endif
