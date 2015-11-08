#include "mipsMemory.h"


int data_mem[DATA_MEM_SIZE];
instruction instr_mem[INSTR_MEM_SIZE];

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


//num_instr to determine end of array or if array must be resized
//Assuming mipsDecode decodes instructions into an array of instruction structs...
//storing a program becomes changing the instr_mem pointer to the beninning
//of the parsed list.
void save_program(instruction * program, int num_instr){
	// save program at index 0
	// Solve this when we get to decode, but
	// are we sure mips statements will be newline separated?
	
	instr_mem = program;
}


instruction fetch_instr(int address){
	if(address < 0 || address > INSTR_MEM_SIZE){
		//error
	}

	return instr_mem[address];
}

