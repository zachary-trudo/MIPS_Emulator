#include "mipsMemory.h"

//int data_mem[DATA_MEM_SIZE];
//memInstruct instr_mem[INSTR_MEM_SIZE];

//int num_labels = 0;
void initMemInstruct(memInstruct* inst)
{
    inst->rs = (char*) malloc(sizeof(char) * 4);
    inst->rs = '\0';

    inst->rd = (char*) malloc(sizeof(char) * 4);
    inst->rd = '\0';

    inst->rt = (char*) malloc(sizeof(char) * 4);
    inst->rt = '\0';

    inst->imm = (char*) malloc(sizeof(char) * 4);
    inst->imm = '\0';

    inst->addr = (char*) malloc(sizeof(char) * 4);
    inst->addr = '\0';

    inst->LABEL = (char*) malloc(sizeof(char) * 6);
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
        dest->LABEL = (char*) malloc((strlen(src->LABEL) + 1) * sizeof(char));
        strcpy(dest->LABEL, src->LABEL);
    }

    if(src->rt)
    {
        dest->rt = (char*) malloc((strlen(src->rt) + 1) * sizeof(char));
        strcpy(dest->rt, src->rt);
    }

    if(src->rs)
    {
        dest->rs = (char*) malloc((strlen(src->rs) + 1) * sizeof(char));
        strcpy(dest->rs, src->rs);
    }

    if(src->rd)
    {
        dest->rd = (char*) malloc((strlen(src->rd) + 1) * sizeof(char));
        strcpy(dest->rd, src->rd);
    }

    if(src->imm)
    {
        dest->imm = (char*) malloc((strlen(src->imm) + 1) * sizeof(char));
        strcpy(dest->imm, src->imm);
    }

    if(src->addr)
    {
        dest->addr = (char*) malloc((strlen(src->addr) + 1) * sizeof(char));
        strcpy(dest->addr, src->addr);
    }

    if(src->instType)
    {
        dest->instType = src->instType;
        dest->instr = src->instr;
    }
}

void initDataMemory(dataMemory* datMem, int initSize)
{
    int i;
    
    datMem->data = (int*) malloc(sizeof(int) * initSize);
    datMem->size = initSize;
    datMem->used = (int*) malloc(sizeof(int) * initSize);
    
    for(i = 0; i < initSize; i++)
    {
        datMem->data[i] = 0;
        datMem->used[i] = 0;
    }
}

void expandDataMemory(dataMemory* oldDataMemory, int* size)
{
    int oldSize = *size;
    int newSize = *size * 2;
    *size = newSize;
    int i;
    dataMemory* newDataMem = (dataMemory*) malloc((sizeof(dataMemory) * newSize));
    initDataMemory(newDataMem, newSize);

    for(i = 0; i < oldSize;i++)
    {
        newDataMem->data[i] = oldDataMemory->data[i];
        newDataMem->used[i] = oldDataMemory->used[i];
    }

    oldDataMemory = newDataMem;
}

void deleteDataMemory(dataMemory* datMem)
{
    free(datMem->data);
    free(datMem);
}

void setData(dataMemory* datMem, int index, int value)
{
    datMem->data[index] = value;
    datMem->used[index] = 1;
}

void storeData(int* rt, int* ALU_RESULT, int* dataSize, dataMemory* dataMem)
{
    while(*dataSize <= *ALU_RESULT)
    {
        expandDataMemory(dataMem, dataSize);
    }
    setData(dataMem, *ALU_RESULT, *rt);
}

void loadData(int* MEM_ALU_RESULT, int* ALU_RESULT, int* dataSize, dataMemory* dataMem)
{
    if(*ALU_RESULT <= *dataSize)
        *MEM_ALU_RESULT = *(dataMem->data + *ALU_RESULT);
}

int* getDataPointer(char* str, dataMemory* dataMem)
{
    return dataMem->data;
}

int* getSize(dataMemory* dataMem)
{
   return &dataMem->size;
}

int getAddressFromLabel(char * LABEL, const memInstruct* instructs, int numInstructs)
{
	int i;
	int ret = -1;
	charToUpper(LABEL);
	for(i = 0; i < numInstructs; i++)
    {
        if(instructs[i].LABEL)
        {
            if(strcmp(instructs[i].LABEL, LABEL) == 0)
            {
                ret = i;
                break;
            }
        }
	}
	if(ret == -1){
		printf("Undeclared label: %s\n", LABEL);
		exit(0);
	}
	return ret;
}
