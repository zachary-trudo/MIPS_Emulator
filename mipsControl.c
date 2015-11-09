#include "mipsControl.h"
#include "mipsRegisters.h"
#include "mipsMemory.h"
#include "mipsInstructions.h"
#include "mipsInstructionSet.h"
#include <stdio.h>

//make a test program, init necessary registers, save program to instruction memory
int make_test_program(mipsRegister * regs){
	instruction one;
	one.instr = ADD;
	one.dest = "$t1";
	one.src = "$t2";
	one.target = "$t3";

	regs->gp = 0;
	regs->t1 = 0;
	regs->t2 = 5;
	regs->t3 = 7;
	
	instruction * program = {&one};
	save_program(program);

	int instruction_count = 1;
	return instruction_count;
}


//run program, map to correct functions from InstructionSet.h based on instruction type
//manage program counter (global instruction pointer).
int run_program(){
	int instruction_count;
	instruction cur_instr;
	mipsRegister mipsReg = {0};


	instruction_count = make_test_program(&mipsReg);

	program_counter = 0;


	while(program_counter < instruction_count){
		cur_instr = fetch_instr(program_counter);
		program_counter += 1;

		int *src_reg = getPointerToRegister(cur_instr.src, &mipsReg);
		int *target_reg = getPointerToRegister(cur_instr.target, &mipsReg);
		int *dest_reg = getPointerToRegister("$t0", &mipsReg);

		printf("register pointer test %d\n", (dest_reg == (&mipsReg.t0)));
		int result = -1, overflow = 0;

		result = MIPS_ALU(*src_reg, *target_reg, &overflow, cur_instr.instr);
		printf("Result from first instruction: %d \n", result);
	}
	

	printf("Instruction!: %d + %d = %d\n", mipsReg.t2, mipsReg.t3, mipsReg.t0);
	return 0;
}



