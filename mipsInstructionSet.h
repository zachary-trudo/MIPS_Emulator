// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#ifndef __MIPSINSTRUCTIONSET_H__
#define __MIPSINSTRUCTIONSET_H__
#include <stdlib.h>
#include <stdio.h>
#include "mipsRegisters.h" // Contains the mipsRegister struct.
#include "mipsMemory.h"

typedef enum Instructions {ADD, ADDI, ADDU, ADDIU, SUB, SUBI, SUBU, SUBIU, BEQ, BGTZ, BLTZ, BNE, J, LW};

// Arethmetic Operations - Basic arethmetic operations
int MIPS_ADD(int *rd, const int rs, const int rt, int *overFlow);
int MIPS_ADDI(int *rd, const int rs, const int immediate, int *overFlow);
int MIPS_ADDU(int *rd, const int rs, const int rt);
int MIPS_ADDIU(int *rd, const int rs, const int rt);

int MIPS_SUB(int *rd, const int rs, const int rt, int *overFlow);
int MIPS_SUBI(int *rd, const int rs, const int immediate, int *overFlow);
int MIPS_SUBU(int *rd, const int rs, const int rt);
int MIPS_SUBIU(int *rd, const int rs, int immediate);

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
