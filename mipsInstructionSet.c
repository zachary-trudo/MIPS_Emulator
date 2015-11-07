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
        case ADDI:
            returnVal = MIPS_ADDI(rs, rt, overflow);
            break;
        case ADDU:
            returnVal = MIPS_ADDU(rs, rt);
            break;
        case ADDIU:
            returnVal = MIPS_ADDIU(rs, rt);
            break;
        case SUB:
            returnVal = MIPS_SUB(rs, rt, overflow);
            break;
        case SUBI:
            returnVal = MIPS_SUBI(rs, rt, overflow);
            break;
        case SUBU:
            returnVal = MIPS_SUBU(rs, rt);
            break;
        case SUBIU:
            returnVal = MIPS_SUBIU(rs, rt);
            break;

        // Logical Operations:
        case AND:
            returnVal = MIPS_AND(rs, rt);
            break;
        case OR:
            returnVal = MIPS_OR(rs, rt);
            break;

        // Unimplemented Instruction:
        default:
            printf("Unimplemented Instruction, or not R-Type OP: %s\n", instruction);
            exit(1);
            break;
    }
    return returnVal;
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
    *overflow = returnVal < MINVAL;
    return returnVal;
}

// Functionally equivalent to SUB
int MIPS_SUBI(const int rs, const int immediate, int *overflow)
{
    return MIPS_SUB(rs, immediate, overflow);
}


int MIPS_SUBU(const int rs, const int rt);
int MIPS_SUBIU(const int rs, int immediate);

// Logical Operations
int MIPS_AND(const int rs, const int rt);
int MIPS_OR(const int rs, const int rt);

// Branch Operations - Should make basic comparison, and then pass the jump to (MIPS_J) if we really need to jump. 
// According to mips documentation brach operations use the Subtract functions to do the comparison. 
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
