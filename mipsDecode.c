#include "mipsDecode.h"

decodedInstruct* initMipsInstruct()
{
    decodedInstruct* mipsInstruct = (decodedInstruct*) malloc(sizeof(decodedInstruct));
    mipsInstruct->instruction = NONE;
    mipsInstruct->instructType = NONETYPE;
    mipsInstruct->rd = '\0';
    mipsInstruct->rt = '\0';
    mipsInstruct->rs = '\0';
    mipsInstruct->imm = 0;
    mipsInstruct->addr = -1;
    return mipsInstruct;
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
    decodedInstruct* mipsInstruct = initMipsInstruct();


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

