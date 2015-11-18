#include "mipsInstructionStack.h"


void initStackNode(stackNode* theNode)
{
    theNode = (stackNode *) malloc(sizeof(stackNode));
    initMemInstruct(theNode->charInstruct);
    theNode->decodedInstruction = initMipsInstruct();

    // FIXME: This is a bit of dangerous code. I set all nodes to memlocation 0 initially. 
    // This could result in sitations where we get to a point where we miss setting the next instruction and bam - we're back at the beginning. 
    // Honestly, if that happens we'd of been screwed anyway... So I'm not 100% worried about it. 
    theNode->instructMemLocation = 0;
    
    theNode->waiting = FALSE;
}

void deleteStackNode(stackNode* theNode)
{
    deleteMemInstruct(theNode->charInstruct);
    deleteMipsInstruct(theNode->decodedInstruction);
    free(theNode);
}

void initStack(instructStack* theStack)
{
    int i;

    theStack = (instructStack*) malloc(sizeof(instructStack));
    
    for(i = 0; i < STACKSIZE; i++)
    {
        initStackNode(&theStack->nodes[i]);
    }
}

void deleteStack(instructStack* theStack)
{
    int i;

    for(i = 0; i < STACKSIZE; i++)
    {
        deleteStackNode(&theStack->nodes[i]);
    }
    free(theStack);
}


void stack_popBack(instructStack* theStack)
{
    deleteStackNode(&theStack->nodes[STACKSIZE - 1]);
}


// TODO: Currently all instructions go through the entire stack... Obviously that isn't what we want.
// We'll need to redisign the instructions so that they know their path and can jump around. This will
// complicate this function considerably, and require a significant rewrite to major sections of our code.
void stack_cycleStack(instructStack* theStack)
{
    int i = STACKSIZE - 1;
 
    // Back should be complete - So Delete.
    // If we're waiting at WriteBack, something terrible has happened anyway.
    stack_popBack(theStack);

    for(i; i >= 0; i--)
    {
        if(theStack->nodes[i].waiting)
        {
            // FIXME: May not actually need to be fixed, remove notification when a direction is decided.
            // Currently I'm assuming that as soon as we wait, we wait for the rest of the stack.
            // Doing it this way we'll be able to mitigate any conflicts pretty easily. 
            theStack->nodes[i].waiting = FALSE;
            break;
        }
        theStack->nodes[i+1] = theStack->nodes[i];
    }

    if (i == 0)
    {
        initStackNode(&theStack->nodes[i]);
    }
}

        
