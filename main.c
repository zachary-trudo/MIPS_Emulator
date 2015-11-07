// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#include <stdio.h>
#include <stdlib.h>
#include "mipsRegisters.h"
#include "mipsInstructionSet.h"
#include "mipsMemory.h"

typedef enum {FALSE, TRUE} bool;


int main(int argc, char *argv[])
{
    // Open instruction file. 
    FILE *fp;
    fp = fopen(argv[1], "r");

    // Initialize all registers to 0.
    mipsRegisters mipsReg = {0};



    while(TRUE)
    {


    }
    

    return 0;
}
