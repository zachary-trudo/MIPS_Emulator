#ifndef __MIPSREGISTERS_H__
#define __MIPSREGISTERS_H__
#include <stdlib.h>
#include <stdio.h>


struct registers
{
    // Zero is always zero. 
    int zero;

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

    // Temporary Registers - Supposed to be 0'd after use;
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

    // Stack poiunter - Unused
    int sp;

    // Return Address - Unused
    int ra;
} mipsRegisters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

typedef struct registers mipsRegister;

#endif
