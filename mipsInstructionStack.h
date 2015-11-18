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
typedef struct instStackNode {
    int instructMemLocation;
    memInstruct* charInstruct;
    decodedInstruct* decodedInstruction;
    bool waiting;
} stackNode; 

void initStackNode(stackNode* theNode);
void deleteStackNode(stackNode* theNode);

// TODO: This struct may end up being unneeded. We'll see. 
typedef struct instructionStack 
{
    // We'll want 6 nodes. One for each of the steps and one for the next branch. 
    stackNode nodes[STACKSIZE];
} instructStack;

void initStack(instructStack* theStack);
void deleteStack(instructStack* theStack);


