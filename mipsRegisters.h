// Author:          Zachary A Trudo
// Changelog:       Initial Creation - Nov, 6 2015
#ifndef __MIPSREGISTERS_H__
#define __MIPSREGISTERS_H__
#include <stdlib.h>
#include <stdio.h>



// While mips registers could be easily represented as an array of 32 ints, this way we can 
// reference them in a similar fasion to how they would be referenced in assembly.
struct registers
{
    // Zero is always zero.
    const int zero;

    // Aseembler Temporary
    int at;

    // Function Result Registers
    int v0;
    int v1;

    // Function Argument Registers
    int a0;
    int a1;
    int a2;
    int a3;

    // Temporary Registers - Supposed to be 0'd after use
    // Not sure if we'll be bothering with zeroing.
    int t0;
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    int t7;
    int t8;
    int t9;

    // Saved Registers - Preserved across calls.
    int s0;
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    int s6;
    int s7;
    int s8;

    // Kernal Registers - Unused
    int k0;
    int k1;

    // Global Pointer - Unused
    int gp;

    // Stack poiunter
    int sp;

    // Return Address
    int ra;
};

typedef struct registers mipsRegister;

void setRegister(int val, char * reg, mipsRegister *mipsReg);
int getRegister(char * reg, mipsRegister *mipsReg);



int* getPointerToRegister(char* const desiredReg, mipsRegister *mipsReg);
#endif
