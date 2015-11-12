// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mipsRegisters.h"
#include "mipsInstructionSet.h"
#include "mipsMemory.h"
#include "mipsDecode.h"

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
    memInstruct instructMem[1024];
    int instructMemSize = 0;

    parseFile(infp, instructMem, &instructMemSize);
 //   writeFile(outfp, instructMem, instructMemSize);

    // Initialize all registers to 0.
    mipsRegister* mipsReg = (mipsRegister*) malloc(sizeof(mipsRegister));
    initRegister(mipsReg);

    // Initialize all data.
    dataMemory* dataReg = (dataMemory*) malloc(sizeof(dataMemory));
    initDataMemory(dataReg);

    // Initialize first instruction to 0
    int currentAddress  = 0;
    int nextAddress = 1;
    int overflow = 0;

    memInstruct* currentInstruct;
    decodedInstruct* curDecodedInstruct;

	int * ra, sp;
	ra = getPointerToRegister("$ra", mipsReg);
	sp = getPointerToRegister("$sp", mipsReg);
    while(TRUE)
    {
       // Fetch Instruction
       currentInstruct = &instructMem[currentAddress];
       
       // Decode Instruction
       curDecodedInstruct = instructDecode(instructMem, instructMemSize, currentInstruct, mipsReg, dataReg);
       printf("\n%s", instructNames[currentInstruct->instr]);
	   printf("\t $sp = %d, $ra = %d \n", sp, ra);
       if(curDecodedInstruct->instructType == RTYPE)
       {
            *curDecodedInstruct->rd = MIPS_ALU(*curDecodedInstruct->rs, *curDecodedInstruct->rt, &overflow, curDecodedInstruct->instruction);
       }
       if(curDecodedInstruct->instructType == ITYPE)
       {
           if(curDecodedInstruct->instruction == LW || curDecodedInstruct->instruction == SW)
           {
               MIPS_MEMORY(curDecodedInstruct->rt, curDecodedInstruct->rs, curDecodedInstruct->imm, curDecodedInstruct->instruction, dataReg);
           }
           else if(curDecodedInstruct->instruction == BEQ || curDecodedInstruct->instruction == BNE)
           {
               MIPS_BRANCH(curDecodedInstruct, &nextAddress); 
           }
           else
           {
               *curDecodedInstruct->rt = MIPS_ALU_IMM(*curDecodedInstruct->rs, curDecodedInstruct->imm, &overflow, curDecodedInstruct->instruction);
           }
       }
       if(curDecodedInstruct->instructType == JTYPE)
       {
           // MIPS_J(curDecodedInstruct->addr, &nextAddress);
			printf("\t decoded a JTYPE: %s \n", instructNames[curDecodedInstruct->instruction]);
			switch(curDecodedInstruct->instruction){
				case J:
		            MIPS_J(curDecodedInstruct->addr, &nextAddress);
				case JR:
					printf("\tGot a JR instr \n");
					MIPS_JR(curDecodedInstruct->rs,  &nextAddress);
				case JAL:
					MIPS_JAL(curDecodedInstruct->addr, &nextAddress);
				//default:
					//printf("\tbad jump instruction\n");
			}
       }
       if(curDecodedInstruct->instructType == NONETYPE)
       {
		   printf("\tinstruction is nonetype\n, hopefully this exits\n");
           if(currentAddress == instructMemSize - 1)
           {
               break;
           }


       }
        
       wait(10);

       // Execute
       //executeInstruct(currentInstruct, &mipsReg, &currentAddress);
       //
       currentAddress = nextAddress;
       nextAddress++;
    }
  
    for(i = instructMemSize-1; i >= 0; i--)
        deleteMemInstructOnStack(&instructMem[i]);
    close(infp);
    close(outfp);
    return 0;
}
