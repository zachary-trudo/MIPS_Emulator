#ifndef __MIPS_INSTRUCTION_QUEUE_H__
#define __MIPS_INSTRUCTION_QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#include "mipsMemory.h"
#include "mipsInstructions.h"
#include "mipsRegisters.h"
#include "mipsDecode.h"
#include "commonFuncts.h"

#define STACKSIZE 6

// The steps are:
// FETCH the instruction from instruction memory.
// DECODE the fetched instruction.
// EXECUTE arimetic // resolve branches
// MEMORY Perform any required load // store 
// WRITEBACK write arimetic results to register file
typedef enum stages {NONESTAGE, FETCH, DECODE, EXECUTE, MEMORY, WRITEBACK} STAGES;

// A struct for the nodes 
typedef struct instQueueNode {
    int instructMemLocation, ALU_RESULT, MEM_ALU_RESULT;
    memInstruct* charInstruct;
    decodedInstruct* decodedInstruction;
    bool waiting, jumping;
    bool noop;
    STAGES stage;
} queueNode; 

void initQueueNode(queueNode* theNode);
void deleteQueueNode(queueNode* theNode);

// TODO: This struct may end up being unneeded. We'll see. 
typedef struct instructionQueue 
{
    // We'll want 6 nodes. One for each of the steps and one for the next branch. 
    queueNode* nodes;
} instructQueue;

void initQueue(instructQueue* theQueue);
void deleteQueue(instructQueue* theQueue);
void noopNodes(instructQueue* theQueue, int index);

bool noDepenedencies(queueNode* curNode, instructQueue queue, STAGES stage); 
#endif
