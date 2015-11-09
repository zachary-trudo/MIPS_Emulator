// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#include <stdio.h>
#include <stdlib.h>
#include "mipsRegisters.h"
#include "mipsInstructionSet.h"
#include "mipsMemory.h"
#include "mipsDecode.h"
#include "mipsControl.h"

typedef enum {FALSE, TRUE} bool;


int main(int argc, char *argv[])
{
    // Open instruction file. 
    FILE *fp;
    fp = fopen(argv[1], "r");

    // Initialize all registers to 0.
    //mipsRegister mipsReg = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	run_program();

    while(TRUE)
    {

		break;
		
    }
    

    return 0;
}
