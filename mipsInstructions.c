#include "mipsInstructions.h"
#include <stdio.h>

const char* instructNames[NUM_OF_INSTRUCTS] = {
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
    "LW", "SW",                          // 2 Item
                                            // 12 ITYPE (13 - 24)
    
    // Jump JTYPE
    "J", "JAL", "JR",                        // 3 JTYPE (25 - 27)
	
	// Save ITYPE
										//1 ITYPE  27
	//Bitwise/shifts - UNUSED
    //"SLL", "SLLV", "SRA", "SRAV", "SRL", "SRLV"     // Unused (27 - )
};

const char* instructTypes[3] = {"RTYPE", "ITYPE", "JTYPE" };

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
		pStr += 1;
    }
}

InstructionType getInstructionType(const Instructions instruct)
{
    InstructionType returnVal = -1;
    if (instruct >= 0 && instruct <= 12)
    {
        returnVal = RTYPE;
    }
    else if (instruct >= 13 && instruct <= 24)
    {
        returnVal = ITYPE;
    }
    else if (instruct >= 25 && instruct <= 27)
    {
        returnVal = JTYPE;
    }

    return returnVal;
}


Instruction getInstructFromChar(char* charInstruct)
{
    Instructions returnVal = -1;
    int i = 0;
	int comp = -1;
    charToUpper(charInstruct);
    for (i; i < NUM_OF_INSTRUCTS;i++)
    {
		comp = strcmp(instructNames[i], charInstruct);
        if(!comp)
        {
            returnVal = i;
            break;
        }
    }
	
    return returnVal;
}
