#ifndef __MIPSREGISTERS_H__
#define __MIPSREGISTERS_H__
#include <stdlib.h>
#include <stdio.h>

// While mips registers could be easily represented as an array of 32 ints, this way we can 
// reference them in a similar fasion to how they would be referenced in assembly.
struct registers
{
    // Zero is always zero.
    int zero;

    // Assembler Temporary
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
    // We ended up deciding not to bother with Zeroing.
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

    // Kernal Registers - Unused
    int k0;
    int k1;

    // Global Pointer - Unused
    int gp;

    // Stack poiunter
    int sp;
	
	int fp;

    // Return Address
    int ra;
};
typedef struct registers mipsRegister;

void printRegister(mipsRegister* mipsReg);
void initRegister(mipsRegister* mipsReg);
char* registerList[32];
int* getPointerToRegister(char* const desiredReg, mipsRegister* mipsReg);
#endif
