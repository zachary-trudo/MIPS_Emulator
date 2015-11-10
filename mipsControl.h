#ifndef __MIPSCONTROL_H__
#define __MIPSCONTROL_H__

#include <stdlib.h>
#include <stdio.h>
#include "mipsRegisters.h"
#include "mipsMemory.h"
#include "mipsInstructions.h"
#include "mipsInstructionSet.h"

//Used this size to hopefully support hash function.
int make_test_program(mipsRegister* regs);
int program_counter;
int run_program(int instruction_count, mipsRegister* mipsReg);
#endif
