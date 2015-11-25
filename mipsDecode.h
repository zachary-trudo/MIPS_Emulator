#ifndef __MIPSDECODE_H__
#define __MIPSDECODE_H__

#include "mipsInstructions.h"
#include "mipsMemory.h"
#include "mipsRegisters.h"

typedef struct decoded
{

    Instructions instruction;
    InstructionType instructType;

    // We use pointers to registers. 
    int *rd;
    int *rt;
    int *rs;
    int imm;
    int addr;

} decodedInstruct;


decodedInstruct* instructDecode(const memInstruct* const allInstructs, const int instructLength, const memInstruct* const instruct, mipsRegister* mipsReg, dataMemory* dataReg);

void initMipsInstruct(decodedInstruct* mipsInstruct);
void copyMipsInstruct(decodedInstruct* dest, decodedInstruct* src);
void deleteMipsInstruct(decodedInstruct* mipsInstruct);

int decodeAddr(const char* const addr, const memInstruct* const allInstructs, const int instructLength);

#endif

