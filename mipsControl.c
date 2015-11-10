#include "mipsControl.h"




int run_program(int instruction_count, mipsRegister* mipsReg){
	memInstruct* cur_instr;
	program_counter = 0;

	int *src_reg;
	int *target_reg;
	int *dest_reg;
	cur_instr = instr_mem;

	int rs, rt;
	while(program_counter < instruction_count){
		program_counter += 1;
		

		/*not sure if this is an accurate model of which instructions use which register
		  might want to use &program_counter for beq, for example	*/
		if(cur_instr->instType==0){
			dest_reg = getPointerToRegister(cur_instr->rd, mipsReg);
			rs = getRegister(cur_instr->rs, mipsReg);
			rt = getRegister(cur_instr->rt, mipsReg);
		}else if(cur_instr->instType==1){
			dest_reg = getPointerToRegister(cur_instr->rt, mipsReg);
			rs = getRegister(cur_instr->rs, mipsReg);
			rt = atoi(cur_instr->imm);
		}else if(cur_instr->instType == 2){
			dest_reg = NULL;
		}

		int result = -1, overflow = 0;

		result = MIPS_ALU(rs,rt, cur_instr->instr, &overflow);
		if(dest_reg != NULL)		
			*dest_reg = result;
		cur_instr++;
	}

	printf("Result ($t3): %d\n", mipsReg->t3);

	return 0;
}



