#include "mipsMemory.h"

int data_mem[DATA_MEM_SIZE];
memInstruct instr_mem[INSTR_MEM_SIZE];

void deleteMemInstruct(memInstruct* inst)
{
    if(inst->rs)
        free(inst->rs);

    if(inst->rt)
        free(inst->rt);

    if(inst->rd)
        free(inst->rd);

    if(inst->imm)
        free(inst->imm);

    if(inst->addr)
        free(inst->addr);

    if(inst->LABEL)
        free(inst->LABEL);
    
    free(inst);
}

void copyInstructMem(memInstruct* const dest, memInstruct* const src)
{
    if(src->LABEL)
    {
        dest->LABEL = (char*) malloc(sizeof(src->LABEL));
        strcpy(dest->LABEL, src->LABEL);
    }

    if(src->rt)
    {
        dest->rt = (char*) malloc(sizeof(src->rt));
        strcpy(dest->rt, src->rt);
    }

    if(src->rs)
    {
        dest->rs = (char*) malloc(sizeof(src->rs));
        strcpy(dest->rs, src->rs);
    }

    if(src->rd)
    {
        dest->rd = (char*) malloc(sizeof(src->rd));
        strcpy(dest->rd, src->rd);
    }

    if(src->imm)
    {
        dest->imm = (char*) malloc(sizeof(src->imm));
        strcpy(dest->imm, src->imm);
    }

    if(src->addr)
    {
        dest->addr = (char*) malloc(sizeof(src->addr));
        strcpy(dest->addr, src->addr);
    }

    if(src->instType)
    {
        dest->instType = src->instType;
        dest->instr = src->instr;
    }
}









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

