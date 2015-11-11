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


int decodeAddr(const char* const addr, const memInstruct* const allInstructs, const int instructLength)
{
    int returnVal = 0;
    int found = 0;
    memInstruct* instructPtr = allInstructs;

    for (returnVal = 0; returnVal < instructLength; returnVal++) 
    {
        if(strcmp(instructPtr->LABEL, addr) == 0)
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
    printf("Didn't find the label.... ending");
    exit(1);
}



decodedInstruct* instructDecode(const memInstruct* const allInstructs, const int instructLength, const memInstruct* const instruct, mipsRegister* mipsReg, dataMemory* dataReg)
{
    decodedInstruct* mipsInstruct = initMipsInstruct();

    if(instruct->addr)
    {
        mipsInstruct->addr = decodeAddr(instruct->addr, allInstructs, instructLength);
    }
    if(instruct->rs)
    {
        if(instruct->instr == LW || instruct->instr == SW)
        {
            mipsInstruct->rs = getDataPointer(instruct->rs, dataReg);
        }
        else
        {
            mipsInstruct->rs = getPointerToRegister(instruct->rs, mipsReg);
        }
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
    
    mipsInstruct->instruction = instruct->instr;
    mipsInstruct->instructType = instruct->instType;

    return mipsInstruct;
}

