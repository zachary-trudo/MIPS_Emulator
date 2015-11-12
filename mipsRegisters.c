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


    mipsReg->k0   = 0;
    mipsReg->k1   = 0;

    mipsReg->gp   = 0;

    mipsReg->sp   = 0;
	mipsReg->fp   = 0;
    mipsReg->ra   = 0;
}


struct charToRegister {
    char* str;
    int* reg;
};

void printRegister(mipsRegister* mipsReg)
{
    printf("\n$zero ,%i\n", mipsReg->zero);
    printf("$at ,%i\n", mipsReg->at);
    
    printf("$v0 ,%i\n", mipsReg->v0);
    printf("$v1 ,%i\n", mipsReg->v1);

    printf("$a0 ,%i\n", mipsReg->a0);
    printf("$a1 ,%i\n", mipsReg->a1);
    printf("$a2 ,%i\n", mipsReg->a2);
    printf("$a3 ,%i\n", mipsReg->a3);

    printf("$t0 ,%i\n", mipsReg->t0);
    printf("$t1 ,%i\n", mipsReg->t1);
    printf("$t2 ,%i\n", mipsReg->t2);
    printf("$t3 ,%i\n", mipsReg->t3);
    printf("$t4 ,%i\n", mipsReg->t4);
    printf("$t5 ,%i\n", mipsReg->t5);
    printf("$t6 ,%i\n", mipsReg->t6);
    printf("$t7 ,%i\n", mipsReg->t7);
    printf("$t8 ,%i\n", mipsReg->t8);
    printf("$t9 ,%i\n", mipsReg->t9);

    printf("$s0 ,%i\n", mipsReg->s0);
    printf("$s1 ,%i\n", mipsReg->s1);
    printf("$s2 ,%i\n", mipsReg->s2);
    printf("$s3 ,%i\n", mipsReg->s3);
    printf("$s4 ,%i\n", mipsReg->s4);
    printf("$s5 ,%i\n", mipsReg->s5);
    printf("$s6 ,%i\n", mipsReg->s6);
    printf("$s7 ,%i\n", mipsReg->s7);

    printf("$k0 ,%i\n", mipsReg->k0);
    printf("$k1 ,%i\n", mipsReg->k1);

    printf("$gp ,%i\n", mipsReg->gp);

    printf("$sp ,%i\n", mipsReg->sp);
    printf("$ra ,%i\n", mipsReg->ra);
}





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

        "$k0",      &mipsReg->k0,
        "$k1",      &mipsReg->k1,

        "$gp",      &mipsReg->gp,

        "$sp",      &mipsReg->sp,
        
		"$fp", 		&mipsReg->fp,
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
