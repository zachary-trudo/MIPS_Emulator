#ifndef __MIPSINSTRUCTIONS_H__
#define __MIPSINSTRUCTIONS_H__

#include <stdio.h>
#include <string.h>

#define NUM_OF_INSTRUCTS 30 

typedef enum instructs  {
    NONE,                                           // 1 NONE (0)
	//Arithmetic RTYPE
	ADD, ADDU, SUB, SUBU, MULT, MULTU, DIV, DIVU,   // 8 Items
    // Logical RTYPE
	AND, NOR, OR, XOR,                              // 4 Items
	// SetLessThan RTYPE
    SLT, SLTU,                                       // 2 Item
                                                    // 14 RTYPE (1 - 14)

    // Arithmetic ITYPE
    ADDI, ADDIU, SUBI, SUBIU,                       // 4 Items
    // Logical ITYPE
    ORI, XORI,                                      // 2 Items
    // Branch ITYPE
    BEQ, BGTZ, BLTZ, BNE,                           // 4 Items
    // Load ITYPE
    LW,                                             // 1 Item
    // Store ITYPE
    SW,                                             // 1 Item
                                                    // 12 ITYPE (15 - 26)
    
    // Jump JTYPE
    J, JAL, JR                                      // 3 JTYPE (27 - 29)

	//Bitwise/shifts - UNUSED
	//SLL, SLLV, SRA, SRAV, SRL, SRLV                 // Unused (29 - )
} Instructions;

typedef enum instuctType {NONETYPE, RTYPE, ITYPE, JTYPE} InstructionType;

extern const char* instructNames[NUM_OF_INSTRUCTS];
extern const char* instructTypes[4];

void charToUpper(char* str);

InstructionType getInstructionType(const Instructions instruct);
Instructions getInstructFromChar(char* charInstruct);

#endif
