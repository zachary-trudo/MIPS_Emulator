// Author:      Zachary A Trudo
// Change Log:  Initial Commit - Nov 6, 2015
//              Fleshed out all the instructions - Nov 7, 2015
#include <stdio.h>
#include "mipsInstructionSet.h"


// Mips ALU, should work.
int MIPS_ALU(const int rs, const int rt, int *overflow, const Instructions instruction)
{
    int returnVal = 0;
    switch(instruction)
    {
        // Arithmetic Ops:
        case ADD:
            returnVal = MIPS_ADD(rs, rt, overflow);
            break;
        case ADDU:
            returnVal = MIPS_ADDU(rs, rt);
            break;
        case SUB:
            returnVal = MIPS_SUB(rs, rt, overflow);
            break;
        case SUBU:
            returnVal = MIPS_SUBU(rs, rt);
            break;

        // Logical Operations:
        case AND:
            returnVal = MIPS_AND(rs, rt);
            break;
        case OR:
            returnVal = MIPS_OR(rs, rt);
            break;

        case SLT:
            returnVal = MIPS_SLT(rs, rt);
            break;
        case SLTU:
            returnVal = MIPS_SLTU(rs, rt);
            break;

        // Unimplemented Instruction:
        default:
            printf("Unimplemented Instruction, or not R-Type OP: %s\n", instructNames[instruction]);
            exit(1);
            break;
    }
    return returnVal;
}

int MIPS_ALU_IMM(const int rs, const int rt, int *overflow, const Instructions instruction)
{
    int returnVal = 0;
    switch(instruction)
    {
        // Arithmetic Ops:
        case ADDI:
            returnVal = MIPS_ADDI(rs, rt, overflow);
            break;
        case ADDIU:
            returnVal = MIPS_ADDIU(rs, rt);
            break;
        case SUBI:
            returnVal = MIPS_SUBI(rs, rt, overflow);
            break;
        case SUBIU:
            returnVal = MIPS_SUBIU(rs, rt);
            break;

        // Unimplemented Instruction:
        default:
            printf("Unimplemented Instruction, or not I-Type OP: %s\n", instructNames[instruction]);
            exit(1);
            break;
    }
    return returnVal;
}


void MIPS_MEMORY(int* rt, int* rs, const int imm, const Instructions instruction, dataMemory* datMem)
{
    int* dataSize = getSize(datMem);
    switch(instruction)
    {
        case SW:
            MIPS_SW(imm, rs, dataSize, *rt);
            break;
        case LW:
            MIPS_LW(imm, rs, dataSize, rt);
            break;
        default:
            printf("sOmEtHiNg went terribly wrong. Should be impossible to get here.");
            exit(1);
            break;
    }
}

void MIPS_BRANCH(decodedInstruct* curInstruct, int* nextAddress)
{
    if(curInstruct->instruction == BEQ)
    {
        MIPS_BEQ(*curInstruct->rs, *curInstruct->rt, curInstruct->addr, nextAddress);
    }
    else if(curInstruct->instruction == BNE)
    {
        MIPS_BEQ(*curInstruct->rs, *curInstruct->rt, curInstruct->addr, nextAddress);
    }
}



// Arithmetic Operations - Basic arithmetic operations
int MIPS_ADD(const int rs, const int rt, int *overflow)
{
    int returnVal = rs + rt;
    *overflow = returnVal > MAXVALUE;
    return returnVal;
}

// The functionality of ADDI is exactly the same as ADD... so I'm just going to call it.
int MIPS_ADDI(const int rs, const int immediate, int *overflow)
{
    return MIPS_ADD(rs, immediate, overflow);
}

// ADDU doesn't care about overflow - so we don't set or unset it. 
int MIPS_ADDU(const int rs, const int rt)
{
    return rs + rt;
}

// Funtionally equivalent to ADDU.
int MIPS_ADDIU(const int rs, const int rt)
{
    return MIPS_ADDU(rs, rt);
}

// Subtract value will be referenced in Branch
int MIPS_SUB(const  int rs, const  int rt, int *overflow)
{
    int returnVal = rs + rt;
    *overflow = returnVal < MINVALUE;
    return returnVal;
}

// Functionally equivalent to SUB
int MIPS_SUBI(const int rs, const int immediate, int *overflow)
{
    return MIPS_SUB(rs, immediate, overflow);
}


int MIPS_SUBU(const int rs, const int rt)
{
    return rs - rt;
}

int MIPS_SUBIU(const int rs, int immediate)
{
    return MIPS_SUBU(rs, immediate);
}

// Logical Operations
int MIPS_AND(const int rs, const int rt)
{
    return rs && rt;
}

int MIPS_OR(const int rs, const int rt)
{
    return rs || rt;
}

// Set Less Than
int MIPS_SLT(const int rs, const int rt)
{
    int retVal = rs < rt;
    printf("%i < %i = %i", rs, rt, retVal);
    return retVal;
}


int MIPS_SLTU(const int rs, const int rt)
{
    int retVal = rs < rt;
    printf("%i < %i = %i", rs, rt, retVal);
    return retVal;
}

// Branch Operations - Should make basic comparison, and then pass the jump to (MIPS_J) if we really need to jump. 
// According to mips documentation brach operations use the Subtract functions to do the comparison. 
void MIPS_BEQ(const int rs, const const int rt, const int addr, int *nextInstruction)
{
    if (MIPS_SUBU(rs, rt) == 0)
    {
        MIPS_J(addr, nextInstruction);
    }
}


void MIPS_BNE(const int rs, const int rt, const int addr, int *nextInstruction)
{
    if (MIPS_SUBU(rs, rt) != 0)
    {
        MIPS_J(addr, nextInstruction);
    }
}

// Jump Operations - I think we should have a "Next Instruction" global. This could just change where it is pointing to. 
void MIPS_J(int addr, int *nextAddress)
{
    *nextAddress = addr;
}

// Load Operations

// imm = index * 4, rs = addr
void MIPS_LW(int imm, int* rs, int* size, int* rt)
{
    *rt = loadData(rs, size, imm / 4);
}

// imm = index, rs = addr, size = size, rt = storeValue
// Returns0 for failure, 1 for success.
void MIPS_SW(int imm, int* rs, int* size, int rt)
{
    storeData(rs, size, imm / 4, rt);
}




// TODO: There are actually a lot of commands I haven't included we'll need to flesh out all of them most likely. -Zach 6 Nov 2015

