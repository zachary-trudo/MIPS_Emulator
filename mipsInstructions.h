#ifndef __MIPSINSTRUCTIONS_H__
#define __MIPSINSTRUCTIONS_H__

#include <string.h>

#define NUM_OF_INSTRUCTS 28 

typedef enum instructs  {
	//Arithmetic RTYPE
	ADD, ADDU, SUB, SUBU, MULT, MULTU, DIV, DIVU,   // 8 Items
    // Logical RTYPE
	AND, NOR, OR, XOR,                              // 4 Items
	// SetLessThan RTYPE
    SLT,                                            // 1 Item
                                                    // 13 RTYPE (0 - 12)
	/*need to support
	slti, sltiu, sltu
	*/

    // Arithmetic ITYPE
    ADDI, ADDIU, SUBI, SUBIU,                       // 4 Items
    // Logical ITYPE
    ORI, XORI,                                      // 2 Items
    // Branch ITYPE
    BEQ, BGTZ, BLTZ, BNE,                           // 4 Items
    // Load ITYPE
    LW,                                             // 1 Item
                                                    // 11 ITYPE (13 - 23)
    
    // Jump JTYPE
    J, JAL, JR,                                      // 3 JTYPE (24 - 26)

	// Save ITYPE
	SW												//1 ITYPE
	//Bitwise/shifts - UNUSED
	//SLL, SLLV, SRA, SRAV, SRL, SRLV                 // Unused (27 - )
} Instructions;

typedef enum instuctType { RTYPE, ITYPE, JTYPE} InstructionType;
extern const char* instructNames[NUM_OF_INSTRUCTS];
extern const char* instructTypes[3];

void charToUpper(char* str);
InstructionType getInstructionType(const Instructions instruct);
Instructions getInstructFromChar(char* charInstruct);

#endif

