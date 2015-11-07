// Author:          Zachary A Trudo
// Changelog:       Initial Creation - Nov 6, 2015
#ifndef __MIPSMEMORY_H__
#define __MIPSMEMORY_H__

typedef struct instructMemory
{
    int a;
} instructionMemory;

typedef struct dataMemory
{
    int a;
} dataMemory;

extern const int DATA_MEM_SIZE = 1028;
extern const int INSTR_MEM_SIZE = 1028;

extern int data_mem[];
extern int instr_mem[];

void save_data(int address, char* value);
void load_data(int address);

void save_program(char * program);
void fetch_instr(int address);
#endif
