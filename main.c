// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#include <stdio.h>
#include <stdlib.h>
#include "mipsRegisters.h"
#include "mipsInstructionSet.h"
#include "mipsMemory.h"
#include "mipsDecode.h"
#include "mipsControl.h"
#include "mipsParseFile.h"

typedef enum {FALSE, TRUE} bool;


int main(int argc, char *argv[])
{
    // Open instruction file. 
    FILE *fp;

    if(argv[1])
        fp = fopen(argv[1], "r");

	int instr_mem_size = INSTR_MEM_SIZE;
    // Initialize all registers to 0.
    mipsRegister mipsReg = {0};
	parseFile(fp, instr_mem, &instr_mem_size);
	memInstruct* instr;
	
	int j;
	printf("linenumber - instType - instr - reg/addr - reg/imm(reg) - reg/imm/addr\n");
	//Just used 3 here for instruction count, running with test.asm
	for(j=0;j<3;j++){
		if((instr_mem+j)->instType == 1){
			printf("%d \t %d \t  %d \t %s \t %s \t %s \n",j, (instr_mem+j)->instType, (instr_mem+j)->instr, (instr_mem+j)->rt, (instr_mem+j)->rs, (instr_mem+j)->imm);
		}else if ((instr_mem+j)->instType == 2){
			printf("%d \t %d \t %d \t %s\n", j, (instr_mem+j)->instType, (instr_mem+j)->instr, (instr_mem+j)->addr);
		}else{
			printf("%d \t %d \t %d \t %s \t %s \t %s \n",j,(instr_mem+j)->instType, (instr_mem+j)->instr, (instr_mem+j)->rd, (instr_mem+j)->rs,(instr_mem+j)->rt);
		}

	}
	
	//Just used 3 here for instruction count, running with test.asm
	run_program(3, &mipsReg);
	
    while(TRUE)
    {
		
		break;
		
    }
    

    return 0;
}
