#include "mipsInstructions.h"

const char* instructNames[31] = {
	//Arithmetic RTYPE
	"ADD", "ADDU", "SUB", "SUBU", "MULT", "MULTU", "DIV", "DIVU",   // 8 Items
    // Logical RTYPE
	"AND", "NOR", "OR", "XOR",                                      // 4 Items
	// SetLessThan RTYPE
    "SLT",                                                          // 1 Item
                                                                    // 13 RTYPE (0 - 12)

    // Arithmetic ITYPE
    "ADDI", "ADDIU", "SUBI", "SUBIU",       // 4 Items
    // Logical ITYPE
    "ORI", "XORI",                          // 2 Items
    // Branch ITYPE
    "BEQ", "BGTZ", "BLTZ", "BNE",           // 4 Items
    // Load ITYPE
    "LW",                                   // 1 Item
                                            // 11 ITYPE (13 - 23)
    
    // Jump JTYPE
    "J", "JAL", "JR",                        // 3 JTYPE (24 - 26)

	//Bitwise/shifts - UNUSED
    "SLL", "SLLV", "SRA", "SRAV", "SRL", "SRLV"     // Unused (27 - )
};

// Because C sucks it doesn't have an .upper function... I hate C.
void charToUpper(char* str)
{
    char* pStr = str;

    while(*pStr != '\0')
    {
        if (*pStr >= 'a' && *pStr <= 'z')
        {
            *pStr -= 'a';
            *pStr += 'A';
        }
    }
}

InstructionType getInstructionType(Instruction instruct)
{
    InstructionType returnVal = NULL;
    if (instruct >= 0 && instruct <= 12)
    {
        returnVal = RTYPE;
    }
    else if (instruct >= 13 && instruct <= 23)
    {
        returnVal = ITYPE;
    }
    else if (instruct >= 24 && instruct <= 26)
    {
        returnVal = JTYPE;
    }

    return returnVal;
}


Instructions getInstructFromChar(char* charInstruct)
{
    Instruction returnVal = NULL;
    int i = 0;
    int len = sizeof(instructNames) / sizeof(char);

    charToUpper(charInstruct);

    for (i; i < len;i++)
    {
        if(strcmp(instructNames[i], charInstruct))
        {
            returnVal = i;
            break;
        }
    }

    return returnVal;
}
