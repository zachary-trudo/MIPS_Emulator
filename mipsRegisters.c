#include "mipsRegisters.h"

void initRegister(mipsRegister* mipsReg)
{
    mipsReg->zero = 0;
    mipsReg->at   = 0;

    mipsReg->v0   = 0;
    mipsReg->v1   = 0;

    mipsReg->a0   = 0;
    mipsReg->a1   = 0;
    mipsReg->a2   = 0;
    mipsReg->a3   = 0;

    mipsReg->t0   = 0;
    mipsReg->t1   = 0;
    mipsReg->t2   = 0;
    mipsReg->t3   = 0;
    mipsReg->t4   = 0;
    mipsReg->t5   = 0;
    mipsReg->t6   = 0;
    mipsReg->t7   = 0;
    mipsReg->t8   = 0;
    mipsReg->t9   = 0;

    mipsReg->s0   = 0;
    mipsReg->s1   = 0;
    mipsReg->s2   = 0;
    mipsReg->s3   = 0;
    mipsReg->s4   = 0;
    mipsReg->s5   = 0;
    mipsReg->s6   = 0;
    mipsReg->s7   = 0;
    mipsReg->s8   = 0;


    mipsReg->k0   = 0;
    mipsReg->k1   = 0;

    mipsReg->gp   = 0;

    mipsReg->sp   = 0;

    mipsReg->ra   = 0;
}


struct charToRegister {
    char* str;
    int* reg;
};


int* getPointerToRegister(char* const desiredReg, mipsRegister* mipsReg)
{
    
    struct charToRegister c2rDict[] =
    {
        "$zero",    &mipsReg->zero,
        "$0",       &mipsReg->zero,
        
        "$at",      &mipsReg->at,
        
        "$v0",      &mipsReg->v0,
        "$v1",      &mipsReg->v1,
        
        "$a0",      &mipsReg->a0,
        "$a1",      &mipsReg->a1,
        "$a2",      &mipsReg->a2,
        "$a3",      &mipsReg->a3,
        
        "$t0",      &mipsReg->t0,
        "$t1",      &mipsReg->t1,
        "$t2",      &mipsReg->t2,
        "$t3",      &mipsReg->t3,
        "$t4",      &mipsReg->t4,
        "$t5",      &mipsReg->t5,
        "$t6",      &mipsReg->t6,
        "$t7",      &mipsReg->t7,
        "$t8",      &mipsReg->t8,
        "$t9",      &mipsReg->t9,

        "$s0",      &mipsReg->s0,
        "$s1",      &mipsReg->s1,
        "$s2",      &mipsReg->s2,
        "$s3",      &mipsReg->s3,
        "$s4",      &mipsReg->s4,
        "$s5",      &mipsReg->s5,
        "$s6",      &mipsReg->s6,
        "$s7",      &mipsReg->s7,
        "$s8",      &mipsReg->s8,

        "$k0",      &mipsReg->k0,
        "$k1",      &mipsReg->k1,

        "$gp",      &mipsReg->gp,

        "$sp",      &mipsReg->sp,
        
        "$ra",      &mipsReg->ra
    };

    int lenc2r = 33;
    int i = 0;

    int *retVal = NULL;

    for(i; i < lenc2r; i++)
    {
        if(strcmp(desiredReg, c2rDict[i].str) == 0)
        {
            retVal = c2rDict[i].reg;
        }
    }

    if(retVal)
    {
        return retVal;
    }

    printf("Register: %s, doesn't exist.", desiredReg);
    exit(1);

}
