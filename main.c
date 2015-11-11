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
    writeFile(outfp, instructMem, instructMemSize);

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


    while(TRUE)
    {
       // Fetch Instruction
       currentInstruct = &instructMem[currentAddress];
       
       // Decode Instruction
       curDecodedInstruct = instructDecode(instructMem, instructMemSize, currentInstruct, mipsReg, dataReg);
       printf("\n%s", instructNames[currentInstruct->instr]);

       if(curDecodedInstruct->instructType == RTYPE)
       {
            *curDecodedInstruct->rd = MIPS_ALU(*curDecodedInstruct->rs, *curDecodedInstruct->rt, &overflow, curDecodedInstruct->instruction);
       }
       if(curDecodedInstruct->instructType == ITYPE)
       {
           if(curDecodedInstruct->instruction == LW || curDecodedInstruct->instruction == SW)
           {
               MIPS_MEMORY(curDecodedInstruct->rt, curDecodedInstruct->rs, &curDecodedInstruct->imm, curDecodedInstruct->instruction, dataReg);
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
            MIPS_J(curDecodedInstruct->addr, &nextAddress);
       }
       if(curDecodedInstruct->instructType == NONETYPE)
       {
           if(currentAddress == instructMemSize - 1)
           {
               break;
           }


       }
      
       int returnTime = time(0) + 2;

       // Execute
       //executeInstruct(currentInstruct, &mipsReg, &currentAddress);
       //
       currentAddress = nextAddress;
       nextAddress++;

        printf("\n");
        for(i = 0; i < *getSize(dataReg); i++)
        {
            if(dataReg->data[i] != 0)
                printf("%i : %i\n", i, dataReg->data[i]);
        }
        printf("\n");
        printRegister(mipsReg);

    }
 
    for(i = instructMemSize-1; i >= 0; i--)
        deleteMemInstructOnStack(&instructMem[i]);
    close(infp);
    close(outfp);
    return 0;
}
