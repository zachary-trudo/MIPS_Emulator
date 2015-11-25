#include "mipsStages.h"

// MIPS_FETCH
void MIPS_FETCH(queueNode* currentNode, memInstruct* instructMem, int* PC)
{
    if(currentNode->stage == FETCH)
    {
        initQueueNode(currentNode);
        currentNode->instructMemLocation = *PC;
        (*PC)++;
        copyInstructMem(currentNode->charInstruct, &instructMem[currentNode->instructMemLocation]);
    }
}

// MIPS_DECODE is just a wrapper for instructDecode. 
void MIPS_DECODE(queueNode* currentNode, mipsRegister* mipsReg, dataMemory* dataReg, memInstruct* allInstructs, int instructLength)
{
    if(currentNode->stage == DECODE)
        copyMipsInstruct(currentNode->decodedInstruction, instructDecode(allInstructs, instructLength, currentNode->charInstruct, mipsReg, dataReg));
}

// MIPS_EXECUTE 
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
           if(currentNode->decodedInstruction->instructType == ITYPE)
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
           if(currentNode->decodedInstruction->instructType == JTYPE)
           {
                if(currentNode->decodedInstruction->instruction == J)
                {
                        if(currentNode->decodedInstruction->addr > instructMemSize - 1)
                        {
                            printf("Requested Memory is out of bound.\nRequested Memory: %i\nCurrent Memory Size: %i", currentNode->decodedInstruction->addr, instructMemSize);
                            exit(0);
                        }
                        MIPS_J(currentNode->decodedInstruction->addr, PC);
                        currentNode->jumping = TRUE;
                }
                else if(currentNode->decodedInstruction->instruction == JR)
                {
                        MIPS_JR(mipsReg->ra,  PC);
                        currentNode->jumping = TRUE;
                }
                else if(currentNode->decodedInstruction->instruction == JAL)
                {
                        MIPS_JAL(currentNode->decodedInstruction->addr, PC, mipsReg);
                        currentNode->jumping = TRUE;
                }
           }
        }
        else
        {
            currentNode->waiting = TRUE;
        }
    }
}

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
    }
}

void MIPS_WRITEBACK(queueNode* currentNode, mipsRegister* mipsReg)
{
    if(currentNode->stage == WRITEBACK && currentNode->noop == FALSE)
    {
        if(currentNode->decodedInstruction->instructType == RTYPE)
        {
            *currentNode->decodedInstruction->rd = currentNode->ALU_RESULT;
        }
        if(currentNode->decodedInstruction->instructType == ITYPE)
        {
            if(currentNode->decodedInstruction->instruction != SW && currentNode->decodedInstruction->instruction != LW)
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

bool MIPS_HANDLEJUMPS(instructQueue* theQueue)
{
    bool retVal = theQueue->nodes[3].jumping;
    if(retVal)
    {
        noopNodes(theQueue, 1);
        noopNodes(theQueue, 2);
    }
    return retVal;
}

