// Author:          Zachary A Trudo
// Changelog:       Initial Creation - Nov 6, 2015

#include "mipsInstructions.h"

#ifndef __MIPSMEMORY_H__
#define __MIPSMEMORY_H__



#define DATA_MEM_SIZE 1028
#define INSTR_MEM_SIZE 1028

typedef struct instructionMemory
{
   char * label;
	Instructions instr;
	char * dest;
	char * src;
	char * target;
	
} instructionMemory;

//typedef struct dataMemory
//{
  //  int a;
//} dataMemory;


extern int data_mem[];
extern instructionMemory instr_mem[];

void save_data(int address, int value);
int load_data(int address);

void save_program(char * program);
char* fetch_instr(int address);
#endif
