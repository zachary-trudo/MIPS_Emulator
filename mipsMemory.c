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
    
    datMem->t0 = (int*) malloc(sizeof(int) * initSize);
    datMem->t1 = (int*) malloc(sizeof(int) * initSize);
    datMem->t2 = (int*) malloc(sizeof(int) * initSize);
    datMem->t3 = (int*) malloc(sizeof(int) * initSize);
    datMem->t4 = (int*) malloc(sizeof(int) * initSize);
    datMem->t5 = (int*) malloc(sizeof(int) * initSize);
    datMem->t6 = (int*) malloc(sizeof(int) * initSize);
    datMem->t7 = (int*) malloc(sizeof(int) * initSize);

    datMem->sizet0 = initSize;
    datMem->sizet1 = initSize;
    datMem->sizet2 = initSize;
    datMem->sizet3 = initSize;
    datMem->sizet4 = initSize;
    datMem->sizet5 = initSize;
    datMem->sizet6 = initSize;
    datMem->sizet7 = initSize;
}

void expandDataMemory(int* addr, int* size)
{
    *size = *size * 2;
    int* newAddr = realloc(addr, *size);
    addr = newAddr;
}

void deleteDataMemory(dataMemory* datMem)
{
    free(datMem->t0);
    free(datMem->t1);
    free(datMem->t2);
    free(datMem->t3);
    free(datMem->t4);
    free(datMem->t5);
    free(datMem->t6);
    free(datMem->t7);

    free(datMem);
}


void storeData(int* addr, int* size, int index, int data)
{
    if(*size = index)
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
    int* retVal;
    int arraySize = 8;
    struct char2dataDict dataMap[] = {
        // data, size, str
        dataMem->t0, &dataMem->sizet0, "$t0",
        dataMem->t1, &dataMem->sizet1, "$t1",
        dataMem->t2, &dataMem->sizet2, "$t2",
        dataMem->t3, &dataMem->sizet3, "$t3",
        dataMem->t4, &dataMem->sizet4, "$t4",
        dataMem->t5, &dataMem->sizet5, "$t5",
        dataMem->t6, &dataMem->sizet6, "$t6",
        dataMem->t7, &dataMem->sizet7, "$t7"
    };

    int i;
    for(i = 0; i < arraySize; i++)
    {
        if(strcmp(dataMap[i].str, str) == 0)
        {
            retVal = dataMap[i].data;
            break;
        }
    }

    return retVal;
}

int* getSize(dataMemory* dataMem, int* rs)
{
    int arraySize = 8;
    int* retVal;
    struct char2dataDict dataMap[] = {
        // data, size, str
        dataMem->t0, &dataMem->sizet0, "$t0",
        dataMem->t1, &dataMem->sizet1, "$t1",
        dataMem->t2, &dataMem->sizet2, "$t2",
        dataMem->t3, &dataMem->sizet3, "$t3",
        dataMem->t4, &dataMem->sizet4, "$t4",
        dataMem->t5, &dataMem->sizet5, "$t5",
        dataMem->t6, &dataMem->sizet6, "$t6",
        dataMem->t7, &dataMem->sizet7, "$t7"
    };
    
   int i;
   for (i = 0; i < arraySize; i++)
   {
       if(rs == dataMap[i].data)
       {
            retVal = dataMap[i].size;
            break;
       }
   }

   return retVal;
}

            
            
            
