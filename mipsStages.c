#include "mipsStages.h"

// MIPS_FETCH does a few things.
// It initializes the Node.
// Sets the instructMemLocation to the current one in PC.
// Cycles the PC
// and loads the instruction from instruction memory.
void MIPS_FETCH(queueNode* currentNode, memInstruct* instructMem, int* PC)
{
    if(currentNode->stage == FETCH && currentNode->noop == FALSE)
    {
        //initQueueNode(currentNode);
        currentNode->instructMemLocation = *PC;
        (*PC)++;
        copyInstructMem(currentNode->charInstruct, &instructMem[currentNode->instructMemLocation]);
        currentNode->stage = DECODE;
    }
}

// MIPS_DECODE is just a wrapper for instructDecode, which decodes the string values in the charInstruct to real values in a decodedInstruct. 
void MIPS_DECODE(queueNode* currentNode, mipsRegister* mipsReg, dataMemory* dataReg, memInstruct* allInstructs, int instructLength)
{
    if(currentNode->stage == DECODE && currentNode->noop == FALSE)
    {
        copyMipsInstruct(currentNode->decodedInstruction, instructDecode(allInstructs, instructLength, currentNode->charInstruct, mipsReg, dataReg));
        currentNode->stage = EXECUTE;
    }
}

// MIPS_EXECUTE: Alot of logic here, but in a few sentences this is what we're doing:
// Check if we're actually trying to execute, if so then
// Check if we've any dependencies, we we do - halt.
// Otherwise check our instruct and instruct type and go from there.
// If we're jumping, be sure to set the jumping tag. Jumps occur at branches and any JTYPE. 
void MIPS_EXECUTE(queueNode* currentNode, mipsRegister* mipsReg, int instructMemSize, int* PC, int* overflow, instructQueue queue) 
{
    if(currentNode->stage == EXECUTE && currentNode->noop == FALSE)
    {
        if(noDependencies(currentNode, queue, EXECUTE))
        {
           if(currentNode->decodedInstruction->instructType == RTYPE)
           {
                currentNode->ALU_RESULT = MIPS_ALU(*currentNode->decodedInstruction->rs, *currentNode->decodedInstruction->rt, overflow, currentNode->decodedInstruction->instruction);
           }
           else if(currentNode->decodedInstruction->instructType == ITYPE)
           {
               if(currentNode->decodedInstruction->instruction == LW || currentNode->decodedInstruction->instruction == SW)
               {
                   currentNode->ALU_RESULT = MIPS_ALU_MEMORY(*currentNode->decodedInstruction->rs, currentNode->decodedInstruction->imm, overflow);
               }
               else if(currentNode->decodedInstruction->instruction == BEQ || currentNode->decodedInstruction->instruction == BNE)
               {
                   if(MIPS_BRANCH(currentNode->decodedInstruction, PC))
                   {
                       currentNode->jumping = TRUE;
                   }
               }
               else
               {
                   currentNode->ALU_RESULT = MIPS_ALU_IMM(*currentNode->decodedInstruction->rs, currentNode->decodedInstruction->imm, overflow, currentNode->decodedInstruction->instruction);
               }
           }
           else if(currentNode->decodedInstruction->instructType == JTYPE)
           {
                if(currentNode->decodedInstruction->instruction == J)
                {
                    if(currentNode->decodedInstruction->addr > instructMemSize - 1)
                    {
                        printf("Requested Memory is out of bound.\nRequested Memory: %i\nCurrent Memory Size: %i", currentNode->decodedInstruction->addr, instructMemSize);
                        exit(0);
                    }
                    MIPS_J(currentNode->decodedInstruction->addr, PC);
                }
                else if(currentNode->decodedInstruction->instruction == JR)
                {
                    MIPS_JR(mipsReg->ra,  PC);
                }
                else if(currentNode->decodedInstruction->instruction == JAL)
                {
                    MIPS_JAL(currentNode->decodedInstruction->addr, PC, mipsReg);
                }
                currentNode->jumping = TRUE;
           }
           currentNode->stage = MEMORY;
        }
        else
        {
            currentNode->waiting = TRUE;
        }
    }
}

// MIPS_MEMACCESS
// Only two functions use this stage. Really disappointing that every single operation has to check in at this stage.
void MIPS_MEMACCESS(queueNode* currentNode, mipsRegister* mipsReg, dataMemory* dataReg, int* dataSize)
{
    if(currentNode->stage == MEMORY && currentNode->noop == FALSE)
    {
        if(currentNode->decodedInstruction->instruction == SW)
        {
            MIPS_SW(currentNode->decodedInstruction->rt, &currentNode->ALU_RESULT, dataSize, dataReg);
        }
        else if( currentNode->decodedInstruction->instruction == LW)
        {
            MIPS_LW(&currentNode->MEM_ALU_RESULT, &currentNode->ALU_RESULT, dataSize, dataReg);
        }
        currentNode->stage = WRITEBACK;
    }
}

// MIPS_WRITEBACK:
// There are two types that could writeback: RTYPE and ITYPE.
// RTYPE is easy - take the ALU_RESULT and shove it in the RD.
// ITYPE we need to know if we're a LW or SW. As SW has no writeback,
// and LW actually writes the MEM_ALU_RESULT back instead.
void MIPS_WRITEBACK(queueNode* currentNode, mipsRegister* mipsReg)
{
    if(currentNode->stage == WRITEBACK && currentNode->noop == FALSE)
    {
        if(currentNode->decodedInstruction->instructType == RTYPE)
        {
            *currentNode->decodedInstruction->rd = currentNode->ALU_RESULT;
        }
        else if(currentNode->decodedInstruction->instructType == ITYPE)
        {
            if(currentNode->decodedInstruction->instruction != SW 
            && currentNode->decodedInstruction->instruction != LW 
            && currentNode->decodedInstruction->instruction != BEQ
            && currentNode->decodedInstruction->instruction != BNE)
            {
                *currentNode->decodedInstruction->rt = currentNode->ALU_RESULT;
            }
            else if(currentNode->decodedInstruction->instruction == LW) 
            {
                *currentNode->decodedInstruction->rt = currentNode->MEM_ALU_RESULT;
            }
        }
    }
}

// MIPS_HANDLEJUMPS:
// If we'ere jumping, then we need to noop the FETCH and DECODE nodes. 
void MIPS_HANDLEJUMPS(instructQueue* theQueue)
{
    if(theQueue->nodes[3].jumping)
    {
        noopNodes(theQueue, FETCH);
        noopNodes(theQueue, DECODE);
    }
}

