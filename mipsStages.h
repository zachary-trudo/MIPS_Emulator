#ifndef __MIPS_STAGES_H__
#define __MIPS_STAGES_H__

#include <stdio.h>

#include "commonFuncts.h"
#include "mipsInstructions.h"
#include "mipsInstructionSet.h"
#include "mipsInstructionQueue.h"

void MIPS_FETCH(queueNode* currentNode, memInstruct* instructMem, int* PC);
void MIPS_DECODE(queueNode* currentNode, mipsRegister* mipsReg, dataMemory* dataReg, memInstruct* allInstructs, int instructLength);
void MIPS_EXECUTE(queueNode* currentNode, mipsRegister* mipsReg, int instructMemSize, int* PC, int* overflow, instructQueue queue);
void MIPS_MEMACCESS(queueNode* currentNode, mipsRegister* mipsReg, dataMemory* dataReg, int* dataSize);
void MIPS_WRITEBACK(queueNode* currentNode, mipsRegister* mipsReg);


#endif
