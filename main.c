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

#define INFILEARG 1
#define OUTFILEARG 2

#define INSTRUCTMEMSIZE 200
#define DATAMEMSIZE 100

int main(int argc, char *argv[])
{
    // Open instruction file. 
    FILE *infp, *outfp;
    int i = 0;
    
    if(argv[INFILEARG])
    {
        infp = fopen(argv[INFILEARG], "r");
    }

    if(infp == NULL)
    {
        printf("Didn't get the file\nQuitting\n\n");
        exit(1919); // Cool code for "Exit without getting file." 
    }

    if(argv[OUTFILEARG])
    {
      outfp = fopen(argv[OUTFILEARG], "w");
    }
    else
    {
      outfp = fopen("out.txt", "w");
    }

    memInstruct instructMem[INSTRUCTMEMSIZE];
    int instructMemSize = 0;

    char response;
    printf("\n\nWould you like to use stepMode? (Y or N)");
    response = getchar();
    charToUpper(&response);

    parseFile(infp, instructMem, &instructMemSize);
    writeFile(outfp, instructMem, instructMemSize);
    close(infp);
    close(outfp);

    // Initialize all registers to 0.
    mipsRegister* mipsReg = (mipsRegister*) malloc(sizeof(mipsRegister));
    initRegister(mipsReg);

    // Initialize all data.
    dataMemory* dataReg = (dataMemory*) malloc(sizeof(dataMemory));
    initDataMemory(dataReg, DATAMEMSIZE);

    // Initialize first instruction to 0
    int PC = 0;


    // Initialize the Queue.
    instructQueue*  InstructionQueue = (instructQueue*) malloc(sizeof(instructQueue));
    initQueue(InstructionQueue);

    int overflow = 0;
    int cycles = 0;

    int curTime = 0;

    // Where all the magic happens. 
    while(PC < instructMemSize - 1)
    {
        MIPS_WRITEBACK(&InstructionQueue->nodes[WRITEBACK], mipsReg);
        MIPS_MEMACCESS(&InstructionQueue->nodes[MEMORY], mipsReg, dataReg, &instructMemSize);
        MIPS_EXECUTE(&InstructionQueue->nodes[EXECUTE], mipsReg, instructMemSize, &PC, &overflow, *InstructionQueue);
        MIPS_HANDLEJUMPS(InstructionQueue);
        MIPS_DECODE(&InstructionQueue->nodes[DECODE], mipsReg, dataReg, instructMem, instructMemSize);
        MIPS_FETCH(&InstructionQueue->nodes[FETCH], instructMem, &PC);

        printNode(&InstructionQueue->nodes[WRITEBACK]);
        printNode(&InstructionQueue->nodes[MEMORY]);
        printNode(&InstructionQueue->nodes[EXECUTE]);
        printNode(&InstructionQueue->nodes[DECODE]);
        printNode(&InstructionQueue->nodes[FETCH]);
        printNode(&InstructionQueue->nodes[NONESTAGE]);

        queue_cycleQueue(InstructionQueue);
        cycles++;


        printf("\nPC: %i\nCycles: %i\n", PC, cycles);
        for(i = 0; i < *getSize(dataReg); i++)
        {
            if(dataReg->used[i] == TRUE)
                printf("%i : %i\n", i, dataReg->data[i]);
        }
        printRegister(mipsReg);
        printf("\n");

        //curTime = time(0) + 10;
        //while(curTime > time(0) && PC == 35);
        while(response == 'Y' && getchar() != '\n');
    }

    // Cleanup InstructMem
    for(i = instructMemSize-1; i >= 0; i--)
    {
        deleteMemInstructOnStack(&instructMem[i]);
    }
    // Close our files.
    return 0;
}
