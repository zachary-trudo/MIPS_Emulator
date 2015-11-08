#ifndef __MIPSINSTRUCTIONS_H__
#define __MIPSINSTRUCTIONS_H__


typedef enum instructs  {
	//Arithmetic
	ADD, ADDI, ADDU, ADDIU, SUB, SUBI, SUBU, SUBIU, MULT, MULTU, DIV, DIVU,
	//Logical
	AND,  NOR, OR, ORI, XOR, XORI,
	//Bitwise/shifts
	SLL, SLLV, SRA, SRAV, SRL, SRLV, 
	//Store
	SLT, BEQ, BGTZ, BLTZ, BNE, J, LW
} Instructions;



#endif

/*

instruction parsing logic
read labe lif any
read instruction
type of instruction determines what next 'token' should be
	label, register, or immediate
	
*/
