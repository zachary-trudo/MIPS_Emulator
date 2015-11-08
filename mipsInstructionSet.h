// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#ifndef __MIPSINSTRUCTIONSET_H__
#define __MIPSINSTRUCTIONSET_H__
#include <stdlib.h>
#include <stdio.h>
#include "mipsRegisters.h" // Contains the mipsRegister struct.
#include "mipsMemory.h"

#define MAXVALUE 9999999999
#define MINVALUE -9999999999



extern const char* instructNames[];

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

// Set Less Than
int MIPS_SLT(const int rs, const int rt);
int MIPS_SLTU(const int rs, const int rt);

// Branch Operations - Should make basic comparison, and then pass the jump to (MIPS_J) if we really need to jump. 
// According to mips documentation brach operations use the Subtract functions to do the comparison. 
int MIPS_BEQ(const int rs, const int rt, char *LABEL, int *nextInstruction);
int MIPS_BGTZ(const int rs, char *LABEL, int *nextInstruction);
int MIPS_BLTZ(const int rs, char *LABEL, int *nextInstruction);
int MIPS_BNE(const int rs, const int rt, char *LABEL, int *nextInstruction);

// Jump Operations - I think we should have a "Next Instruction" global. This could just change where it is pointing to. 
int MIPS_J(char *LABEL, int *nextInstruction);

// Load Operations
//int MIPS_LW(const int rt, memoryAddress *location); 

// TODO: There are actually a lot of commands I haven't included we'll need to flesh out all of them most likely. -Zach 6 Nov 2015

#endif
