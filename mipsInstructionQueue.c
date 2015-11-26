#include "mipsInstructionQueue.h"

// Initializes a node.
// FIXME: We need to go through and check our initialization and construction of nodes.
// I think we've got memory leaks here. --Zach
void initQueueNode(queueNode* theNode)
{
    theNode->charInstruct = (memInstruct*) malloc(sizeof(memInstruct));
    initMemInstruct(theNode->charInstruct);

    theNode->decodedInstruction = (decodedInstruct*) malloc(sizeof(decodedInstruct));
    initMipsInstruct(theNode->decodedInstruction);

    theNode->instructMemLocation = 0;
    theNode->ALU_RESULT = 0;
    theNode->MEM_ALU_RESULT = 0;
   
    theNode->jumping = FALSE;
    theNode->waiting = FALSE;
    theNode->noop = FALSE;
    theNode->stage = FETCH;
}

// This prints out some useful information for tracking issues.
// Should be turned off in final iteration.
void printNode(queueNode* theNode)
{
    printf("\n");
    printf("MemAddress: %i, Stage: %i, Jumping: %i, NOOP: %i", theNode->instructMemLocation, theNode->stage, theNode->jumping, theNode->noop);
}

// Deep copy a node creating new memory. 
void copyQueueNode(queueNode* dest, queueNode* src)
{
    if(src->charInstruct)
    {
        dest->charInstruct = (memInstruct*) malloc(sizeof(memInstruct));
        copyInstructMem(dest->charInstruct, src->charInstruct);
    }

    if(src->decodedInstruction)
    {
        dest->decodedInstruction = (decodedInstruct*) malloc(sizeof(decodedInstruct));
        copyMipsInstruct(dest->decodedInstruction, src->decodedInstruction);
    }

    dest->ALU_RESULT = src->ALU_RESULT;
    dest->MEM_ALU_RESULT = src->MEM_ALU_RESULT;
    dest->instructMemLocation = src->instructMemLocation;
    dest->waiting = src->waiting;
    dest->noop = src->noop;
    dest->stage = src->stage;
    dest->jumping = src->jumping;
}

// Deletes a node. 
void deleteQueueNode(queueNode* theNode)
{
    if(theNode->charInstruct)
    {
        deleteMemInstruct(theNode->charInstruct);
    }
    if(theNode->decodedInstruction)
    {
        deleteMipsInstruct(theNode->decodedInstruction);
    }
    initQueueNode(theNode);
}

// Clears a node of all contents. 
void clearQueueNode(queueNode* theNode)
{
    free(theNode->charInstruct);
    theNode->charInstruct = (memInstruct*) malloc(sizeof(memInstruct));

    free(theNode->decodedInstruction);
    theNode->decodedInstruction = (decodedInstruct*) malloc(sizeof(decodedInstruct*));
}

// Initializes a queue.
void initQueue(instructQueue* theQueue)
{
    int i;
    theQueue->nodes = (queueNode*) malloc(sizeof(queueNode) * 6);
    for(i=0; i < 6; i++)
    {
        initQueueNode(&theQueue->nodes[i]);
    }
}

// Deletes a queue.
void deleteQueue(instructQueue* theQueue)
{
    int i;

    for(i = 0; i < STACKSIZE; i++)
    {
        deleteQueueNode(&theQueue->nodes[i]);
    }
    free(theQueue);
}

// Simple function for nooping. 
void noopNodes(instructQueue* theQueue, int index)
{
    theQueue->nodes[index].noop = TRUE;
}

// Unused function... originally we were going to go with a linked list.
// Pershaps we should have stuck with that. 
void queue_popBack(instructQueue* theQueue)
{
    deleteQueueNode(&theQueue->nodes[STACKSIZE - 1]);
}

// This function cycles the queue up until a wait.
// It also initializes the 0 node if its going to be needed.
void queue_cycleQueue(instructQueue* theQueue)
{
    int i = STACKSIZE - 1;

    for(i; i > 0; i--)
    {
        if(theQueue->nodes[i].waiting)
        {
            theQueue->nodes[i].waiting = FALSE;
            clearQueueNode(&theQueue->nodes[i+1]);
            printf("\nWaiting\n");
            break;
        }
        copyQueueNode(&theQueue->nodes[i], &theQueue->nodes[i-1]);
    }

    if (i == 0)
    {
        initQueueNode(&theQueue->nodes[i]);
    }
}

// Checks for depenedencies. 
// FIXME: This function may not be operating correctly and may be why Fibbonnoci is not working.
// Take a look into it. --Zach 
bool noDependencies(queueNode* curNode, instructQueue queue)
{
    bool retVal = TRUE;
    if(curNode->decodedInstruction && queue.nodes[MEMORY].decodedInstruction)
    {
        int* curPointers[3] = {curNode->decodedInstruction->rt, curNode->decodedInstruction->rd, curNode->decodedInstruction->rs};
        int* queuePointers[3] = {queue.nodes[MEMORY].decodedInstruction->rt, queue.nodes[MEMORY].decodedInstruction->rd, queue.nodes[MEMORY].decodedInstruction->rs};
        int i, j;
        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                if(curPointers[i] != 0 && curPointers[i] == queuePointers[j])
                {
                    retVal = FALSE;
                    break;
                }
            }
        }
    }
    return retVal;
}

    
