#include "mipsDecode.h"

void initMipsInstruct(decodedInstruct* mipsInstruct)
{
    mipsInstruct->instruction = NONE;
    mipsInstruct->instructType = NONETYPE;

    mipsInstruct->rd = (int*) malloc(sizeof(int) * 4);
    *mipsInstruct->rd = 0;
    mipsInstruct->rt = (int*) malloc(sizeof(int) * 4);
    *mipsInstruct->rt = 0;
    mipsInstruct->rs = (int*) malloc(sizeof(int) * 4);
    *mipsInstruct->rs = 0;

    mipsInstruct->imm = 0;
    mipsInstruct->addr = -1;
}

void copyMipsInstruct(decodedInstruct* dest, decodedInstruct* src)
{
    dest->rd = src->rd;
    dest->rt = src->rt;
    dest->rs = src->rs;
    dest->imm = src->imm;
    dest->addr = src->addr;

    dest->instruction = src->instruction;
    dest->instructType = src->instructType;
}

void deleteMipsInstruct(decodedInstruct* mipsInstruct)
{
    free(mipsInstruct);
}

int decodeAddr(const char* const addr, const memInstruct* const allInstructs, const int instructLength)
{
    int returnVal = 0;
    int found = 0;
    memInstruct* instructPtr = allInstructs;
    char* localAddr = (char*) malloc(sizeof(addr));
    strcpy(localAddr, addr);
    charToUpper(localAddr);


    for (returnVal = 0; returnVal < instructLength; returnVal++) 
    {
        if(instructPtr->LABEL && strcmp(instructPtr->LABEL, localAddr) == 0)
        {
            found = 1;
            break;
        }
        instructPtr++;
    }
    if(found)
    {
        return returnVal;
    }
    printf("\nDidn't find the label %s.... ending\n", localAddr);
    exit(1);
}



decodedInstruct* instructDecode(const memInstruct* const allInstructs, const int instructLength, const memInstruct* instruct, mipsRegister* mipsReg, dataMemory* dataReg)
{
    decodedInstruct* mipsInstruct = (decodedInstruct*) malloc(sizeof(decodedInstruct));
    initMipsInstruct(mipsInstruct);
    mipsInstruct->instructType = instruct->instType;	
	if(mipsInstruct->instructType == NONETYPE){
		return mipsInstruct;
	}

    mipsInstruct->instruction = instruct->instr;  

    if(instruct->addr)
    {
		mipsInstruct->addr = getAddressFromLabel(instruct->addr, allInstructs, instructLength);
    }
    if(instruct->rs)
    {
        mipsInstruct->rs = getPointerToRegister(instruct->rs, mipsReg);
    }
    if(instruct->rt)
    {
        mipsInstruct->rt = getPointerToRegister(instruct->rt, mipsReg);
    }
    if(instruct->rd)
    {
        mipsInstruct->rd = getPointerToRegister(instruct->rd, mipsReg);
    }
    if(instruct->imm)
    {
        mipsInstruct->imm = atoi(instruct->imm);
    }

    return mipsInstruct;
}

