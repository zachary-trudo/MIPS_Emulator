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
	init_parser_re();
    // Initialize all registers to 0.
    mipsRegister mipsReg = {0};
	parseFile(fp, instr_mem, &instr_mem_size);
	run_program(1, &mipsReg);

    while(TRUE)
    {

		break;
		
    }
    

    return 0;
}
