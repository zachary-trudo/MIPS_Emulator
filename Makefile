CC=gcc
CFLAGS=-I
DEPS=mipsInstructionSet.c main.c mipsDecode.c mipsInstructionQueue.c mipsInstructions.c mipsMemory.c mipsParseFile.c mipsRegisters.c mipsStages.c

MIPS: $(DEPS) 
	$(CC) $(DEPS) -o mips -lm
