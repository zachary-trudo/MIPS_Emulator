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
    FILE *infp, *outfp;
    int i = 0;
    
    if(argv[1])
        infp = fopen(argv[1], "r");

    if(infp == NULL)
        printf("Didn't get the damn file\n");

    if(argv[2])
      outfp = fopen(argv[2], "w");
    else
      outfp = fopen("out.txt", "w");
    memInstruct* instructMem[1024];
    int instructMemSize = 0;

    parseFile(infp, instructMem, &instructMemSize);
    writeFile(outfp, instructMem, instructMemSize);
/*
    // Initialize all registers to 0.
    mipsRegister mipsReg = {0};
    

	//run_program();

    while(TRUE)
    {

		break;
		
    }
  */
//    for(i = 0; i < instructMemSize; i++)
  //      deleteMemInstruct(&(instructMem[i]));
    close(infp);
    close(outfp);
    return 0;
}
