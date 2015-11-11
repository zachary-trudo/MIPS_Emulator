#include "mipsMemory.h"

int data_mem[DATA_MEM_SIZE];
memInstruct instr_mem[INSTR_MEM_SIZE];

void initMemInstruct(memInstruct* inst)
{
    //inst->rs = (char*) malloc(sizeof(char) * 4);
    inst->rs = '\0';

    //inst->rd = (char*) malloc(sizeof(char) * 4);
    inst->rd = '\0';

    //inst->rt = (char*) malloc(sizeof(char) * 4);
    inst->rt = '\0';

    //inst->imm = (char*) malloc(sizeof(char) * 4);
    inst->imm = '\0';

    //inst->addr = (char*) malloc(sizeof(char) * 4);
    inst->addr = '\0';

    //inst->LABEL = (char*) malloc(sizeof(char) * 6);
    inst->LABEL = '\0';

    inst->instType = NONE;
    inst->instr    = NONE;
}



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

void deleteMemInstructOnStack(memInstruct* inst)
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

void initDataMemory(dataMemory* datMem)
{
    int initSize = 10;
    
    datMem->data = (int*) malloc(sizeof(int) * initSize);
    datMem->size = initSize;
}

void expandDataMemory(int* addr, int* size)
{
    *size = *size * 2;
    int* newAddr = realloc(addr, *size);
    addr = newAddr;
}

void deleteDataMemory(dataMemory* datMem)
{
    free(datMem->data);
    free(datMem);
}


void storeData(int* addr, int* size, int index, int data)
{
    while(*size <= index)
    {
        expandDataMemory(addr, size);
    }
    *(addr + index) = data;
}

int loadData(int* addr, int size, int index)
{
    int retVal = 0;
    if(index <= size)
        retVal = *(addr + index);
    return retVal;
}

int* getDataPointer(char* str, dataMemory* dataMem)
{
    return dataMem->data;
}

int* getSize(dataMemory* dataMem)
{
   return &dataMem->size;
}

            
            
            
