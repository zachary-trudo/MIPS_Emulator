#ifndef __MIPSCONTROL_H__
#define __MIPSCONTROL_H__

#include <stdio.h>
#include "mipsRegisters.h"
#include "mipsMemory.h"
#include "mipsInstructions.h"
#include "mipsInstructionSet.h"


int make_test_program(mipsRegister* regs);
int program_counter;
int run_program(int instruction_count, mipsRegister* mipsReg);
#endif
