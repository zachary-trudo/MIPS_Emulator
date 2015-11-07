#ifndef __MIPSINSTRUCTIONSET_H__
#define __MIPSINSTRUCTIONSET_H__
#include <stdlib.h>
#include <stdio.h>
#include "mipsRegisters.h" // Contains the mipsRegister struct.
#include "mipsMemory.h"


// Arethmetic Operations - Basic arethmetic operations
int MIPS_ADD(mipsRegister *rd, const mipsRegister *rs, const mipsRegister *rt, int *overFlow);
int MIPS_ADDI(mipsRegister *rd, const mipsRegister *rs, int immediate, int *overFlow);
int MIPS_ADDU(mipsRegister *rd, const mipsRegister *rs, mipsRegister *rt);
int MIPS_ADDIU(mipsRegister *rd, const mipsRegister *rs, const mipsRegister *rt);

int MIPS_SUB(mipsRegister *rd, mipsRegister *rs, mipsRegister *rt, int *overFlow);
int MIPS_SUBI(mipsRegister *rd, mipsRegister *rs, int immediate, int *overFlow);
int MIPS_SUBU(mipsRegister *rd, mipsRegister *rs, mipsRegister *rt);
int MIPS_SUBIU(mipsRegister *rd, mipsRegister *rs, int immediate);

// TODO: Decide if we're going to include mult and div. 
// I think we should.

// Branch Operations - Should make basic comparison, and then pass the jump to (MIPS_J) if we really need to jump. 
int MIPS_BEQ(mipsRegister *stored, mipsRegister *temporary, char *LABEL, int *nextInstruction);
int MIPS_BGTZ(mipsRegister *stored, char *LABEL, int *nextInstruction);
int MIPS_BLTZ(mipsRegister *stored, char *LABEL, int *nextInstruction);
int MIPS_BNE(mipsRegister *stored, char *LABEL, int *nextInstruction);

// Jump Operations - I think we should have a "Next Instruction" global. This could just change where it is pointing to. 
int MIPS_J(char *LABEL, int *nextInstruction);

// Load Operations
int MIPS_LW(mipsRegister *temporary, memoryAddress *location); 

#endif
