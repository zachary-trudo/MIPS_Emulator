// Author:      Zachary A Trudo
// Changelog:   Initial Creation - Nov 6, 2015
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "commonFuncts.h"
#include "mipsRegisters.h"
#include "mipsInstructionSet.h"
#include "mipsMemory.h"
#include "mipsDecode.h"
#include "mipsStages.h"
#include "mipsInstructionQueue.h"

#define DATAMEMSIZE 100

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
    initDataMemory(dataReg, DATAMEMSIZE);

    // Initialize first instruction to 0
    int PC = 0;

    instructQueue*  InstructionQueue = (instructQueue*) malloc(sizeof(instructQueue));
    initQueue(InstructionQueue);

    int overflow = 0;
    int cycles = 0;

    int curTime = 0;

    while(PC < instructMemSize - 1)
    {
        MIPS_WRITEBACK(&InstructionQueue->nodes[5], mipsReg);
        MIPS_MEMACCESS(&InstructionQueue->nodes[4], mipsReg, dataReg, &instructMemSize);
        MIPS_EXECUTE(&InstructionQueue->nodes[3], mipsReg, instructMemSize, &PC, &overflow, *InstructionQueue);
        MIPS_DECODE(&InstructionQueue->nodes[2], mipsReg, dataReg, instructMem, instructMemSize);
        MIPS_FETCH(&InstructionQueue->nodes[1], instructMem, &PC);

        queue_cycleQueue(InstructionQueue);
        cycles++;
        printf("\nPC: %i\nCycles: %i\n", PC, cycles);
        for(i = 0; i < *getSize(dataReg); i++)
        {
            if(dataReg->used[i] == 1)
                printf("%i : %i\n", i, dataReg->data[i]);
        }
        printf("\n");

        curTime = time(0) + 2;
        while(curTime > time(0));

    }

    printf("\n");

		
    printf("\n");
    for(i = 0; i < *getSize(dataReg); i++)
    {
        if(dataReg->used[i] == 1)
            printf("%i : %i\n", i, dataReg->data[i]);
    }
    printf("\n");
    for(i = instructMemSize-1; i >= 0; i--)
        deleteMemInstructOnStack(&instructMem[i]);
   	close(infp);
    close(outfp);
    return 0;
}
