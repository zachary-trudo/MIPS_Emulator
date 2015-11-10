#include "mipsRegisters.h"

struct charToRegister {
    char* str;
    int* reg;
};

void setRegister(int val, char * reg, mipsRegister *mipsReg){
	int * reg_ptr = getPointerToRegister(reg, mipsReg);
	
	*reg_ptr=val;
}

int getRegister(char * reg, mipsRegister *mipsReg){
	int * reg_ptr = getPointerToRegister(reg, mipsReg);
	return *reg_ptr;
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
        if(strcmp(desiredReg, c2rDict[i].str)==0)
        {
            return c2rDict[i].reg;
        }
    }

  

    printf("Register: %s, doesn't exist.", desiredReg);
    exit(1);

}
