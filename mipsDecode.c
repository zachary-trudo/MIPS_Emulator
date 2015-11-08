#include "mipsDecode.h"

int MIPS_DECODE(char *instruction){
	switch(instruction){
		case "add":
			return ADD;
		case "addi":
			return ADDI;
		case "addu":
			return ADDU;
		case "addiu":
			return ADDIU;
		case "sub":
			return SUB;
		case "subi":
			return SUBI;
		case "subu":
			return SUBU;
		case "subiu":
			return SUBIU;
		case "and":
			return AND;
		case "or":
			return OR;
		case "slt":
			return SLT;
		case "beq":
			return BEQ;
		case "bgtz":
			return BGTZ;
		case "bltz":
			return BLTZ;
		case "bne":
			return BNE;
		case "j":
			return J;
		case "lw":
			return LW;
	}
}
