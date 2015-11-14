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

struct instructTypeMap 
{
    Instructions instruct;
    InstructionType type;
};

struct instructTypeMap instructTypeDict[] =
{
    NONE, NONETYPE,
    ADD,    RTYPE,
    ADDU,   RTYPE,
	SUB,    RTYPE,
    SUBU,   RTYPE,
    MULT,   RTYPE,
    MULTU,  RTYPE,
    DIV,    RTYPE,
    DIVU,   RTYPE,
	AND,    RTYPE, 
    NOR,    RTYPE, 
    OR,     RTYPE,
    XOR,    RTYPE,
    SLT,    RTYPE, 
    SLTU,   RTYPE,

    ADDI,   ITYPE, 
    ADDIU,  ITYPE, 
    SUBI,   ITYPE, 
    SUBI,   ITYPE,
    ORI,    ITYPE, 
    XORI,   ITYPE,
    BEQ,    ITYPE,
    BGTZ,   ITYPE, 
    BLTZ,   ITYPE, 
    BNE,    ITYPE,
    LW,     ITYPE,
    SW,     ITYPE,
    
    J,      JTYPE, 
    JAL,    JTYPE,
    JR,     JTYPE
};


// Because C sucks it doesn't have an .upper function... I hate C.
// This function takes a string and uppercases all the letters.
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



// Returns the type of the instruction.
InstructionType getInstructionType(const Instructions instruct)
{
    InstructionType returnVal = NONETYPE;
    int i;

    for(i = 0; i < NUM_OF_INSTRUCTS;i++)
    {
        if(instruct == instructTypeDict[i].instruct)
        {
            returnVal = instructTypeDict[i].type;
        }
    }

    return returnVal;
}

// Gets the instruction from a string. 
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
