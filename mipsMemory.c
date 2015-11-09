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


memInstruct fetch_instr(int address){
	if(address < 0 || address > INSTR_MEM_SIZE){
		//error
	}

	return instr_mem[address];
}

