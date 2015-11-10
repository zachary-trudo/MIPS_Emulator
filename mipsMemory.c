#include "mipsMemory.h"

int data_mem[DATA_MEM_SIZE];
memInstruct instr_mem[INSTR_MEM_SIZE];


void save_data(int address, int value){
	if(address < 0 || address > DATA_MEM_SIZE){
		//error here
	}

	data_mem[address] = value;
}

int load_data(int address){
	if(address < 0 || address > INSTR_MEM_SIZE){
		//error
	}
	
	return data_mem[address];
}	

//must call free on returned memInstruct
memInstruct * init_memInstruct(){
	memInstruct * instr;
	instr = (memInstruct*) malloc(sizeof(memInstruct));
	instr->instr = -1;
	strcpy(&instr->rt, "\0");
	strcpy(&instr->rd, "\0");
	strcpy(&instr->rs, "\0");
	strcpy(&instr->imm, "\0");
	strcpy(&instr->addr, "\0");
	strcpy(&instr->LABEL, "\0");

	return instr;
}

void copy_memInstr(memInstruct* destInstr, memInstruct* srcInstr){
	destInstr->instType = srcInstr->instType;
	destInstr->instr = srcInstr->instr;
	strcpy(destInstr->rd, srcInstr->rd);
	strcpy(destInstr->rt, srcInstr->rt);
	strcpy(destInstr->rs, srcInstr->rs);
	strcpy(destInstr->imm, srcInstr->imm);
	strcpy(destInstr->addr, srcInstr->addr);
	strcpy(destInstr->LABEL, srcInstr->LABEL);
}

void save_instr(memInstruct* instr, int line){
	if(line < INSTR_MEM_SIZE){
		copy_memInstr((instr_mem+line),instr);
	}
}
//num_instr to determine end of array or if array must be resized
//Assuming mipsDecode decodes instructions into an array of instruction structs...
//storing a program becomes changing the instr_mem pointer to the beninning
//of the parsed list.
void save_program(const memInstruct* program){
	// save program at index 0
	// Solve this when we get to decode, but
	// are we sure mips statements will be newline separated?
	
	*instr_mem = *program;
}

memInstruct fetch_instr(int address)
{
	if(address < 0 || address > INSTR_MEM_SIZE){
		//error
	}

	return instr_mem[address];
}

