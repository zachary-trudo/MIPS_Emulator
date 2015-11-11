#include "mipsInstructions.h"

const char* instructNames[NUM_OF_INSTRUCTS] = {
    "NONE",                                                         // 1 NONE (0)
	//Arithmetic RTYPE
	"ADD", "ADDU", "SUB", "SUBU", "MULT", "MULTU", "DIV", "DIVU",   // 8 Items
    // Logical RTYPE
	"AND", "NOR", "OR", "XOR",                                      // 4 Items
	// SetLessThan RTYPE
    "SLT","SLTU",                                                    // 2 Item
                                                                    // 14 RTYPE (1 - 14)

    // Arithmetic ITYPE
    "ADDI", "ADDIU", "SUBI", "SUBIU",       // 4 Items
    // Logical ITYPE
    "ORI", "XORI",                          // 2 Items
    // Branch ITYPE
    "BEQ", "BGTZ", "BLTZ", "BNE",           // 4 Items
    // Load ITYPE
    "LW",                                   // 1 Item
    // Store ITYPE                          
    "SW",                                   // 1 Items
                                            // 12 ITYPE (15 - 26)
    
    // Jump JTYPE
    "J", "JAL", "JR"                        // 3 JTYPE (27 - 29)

	//Bitwise/shifts - UNUSED
    //"SLL", "SLLV", "SRA", "SRAV", "SRL", "SRLV"     // Unused (30 - )
};

const char* instructTypes[4] = {"NONETYPE", "RTYPE", "ITYPE", "JTYPE" };

// Because C sucks it doesn't have an .upper function... I hate C.
void charToUpper(char* const str)
{
    char* pStr = str;

    while(*pStr != '\0')
    {
        if (*pStr >= 'a' && *pStr <= 'z')
        {
            *pStr -= 'a';
            *pStr += 'A';
        }
        pStr++;
    }
}

InstructionType getInstructionType(const Instructions instruct)
{
    InstructionType returnVal = NONETYPE;
    if (instruct > 0 && instruct <= 14)
    {
        returnVal = RTYPE;
    }
    else if (instruct >= 15 && instruct <= 26)
    {
        returnVal = ITYPE;
    }
    else if (instruct >= 27 && instruct <= 29)
    {
        returnVal = JTYPE;
    }
    else
    {
        printf("Instruction type unknown");
    }

    return returnVal;
}


Instructions getInstructFromChar(char* charInstruct)
{
    Instructions returnVal = NONE;
    int i = 0;
    int len = NUM_OF_INSTRUCTS;

    charToUpper(charInstruct);

    for (i; i < len;i++)
    {
        if(strcmp(instructNames[i], charInstruct) == 0)
        {
            returnVal = i;
            break;
        }
    }

    return returnVal;
}
