#include "mipsInstructionQueue.h"

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
    theNode->stage = NONESTAGE;
}

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
}

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

void clearQueueNode(queueNode* theNode)
{
    free(theNode->charInstruct);
    theNode->charInstruct = (memInstruct*) malloc(sizeof(memInstruct));

    free(theNode->decodedInstruction);
    theNode->decodedInstruction = (decodedInstruct*) malloc(sizeof(decodedInstruct*));
}

void initQueue(instructQueue* theQueue)
{
    int i;
    theQueue->nodes = (queueNode*) malloc(sizeof(queueNode) * 6);
    for(i=0; i < 6; i++)
    {
        initQueueNode(&theQueue->nodes[i]);
    }
}

void deleteQueue(instructQueue* theQueue)
{
    int i;

    for(i = 0; i < STACKSIZE; i++)
    {
        deleteQueueNode(&theQueue->nodes[i]);
    }
    free(theQueue);
}

void noopNodes(instructQueue* theQueue, int index)
{
    theQueue->nodes[index].decodedInstruction->instructType = NONETYPE;
    theQueue->nodes[index].decodedInstruction->instruction = NONE;
}

void queue_popBack(instructQueue* theQueue)
{
    deleteQueueNode(&theQueue->nodes[STACKSIZE - 1]);
}


// TODO: Currently all instructions go through the entire queue... Obviously that isn't what we want.
// We'll need to redisign the instructions so that they know their path and can jump around. This will
// complicate this function considerably, and require a significant rewrite to major sections of our code.
void queue_cycleQueue(instructQueue* theQueue)
{
    int i = STACKSIZE - 1;

    for(i; i > 0; i--)
    {
        if(theQueue->nodes[i].waiting)
        {
            // FIXME: May not actually need to be fixed, remove notification when a direction is decided.
            // Currently I'm assuming that as soon as we wait, we wait for the rest of the queue.
            // Doing it this way we'll be able to mitigate any conflicts pretty easily. 
            theQueue->nodes[i].waiting = FALSE;
            clearQueueNode(&theQueue->nodes[i+1]);
            break;
        }
        copyQueueNode(&theQueue->nodes[i], &theQueue->nodes[i-1]);
        theQueue->nodes[i].stage = i;
    }

    if (i == 0)
    {
        initQueueNode(&theQueue->nodes[i]);
    }
}

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

    
