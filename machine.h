#ifndef MACHINE_H
#define MACHINE_H

#include "instruction.h"
#include "machine_types.h"
#include "stack.h"

#define MAX_MEMORY_SIZE 32768 
#define MAX_DATA_LINE_LENGTH 59
#define DATA_SEPARATOR "        ...     "

//our union (mainMemory is for instructions, all other data in stack memory, temp vars are to be deleted later)
extern union mem_u {
word_type words[MAX_MEMORY_SIZE];
uword_type uwords[MAX_MEMORY_SIZE];
bin_instr_t instrs[MAX_MEMORY_SIZE];
} mainMemory, tempMem1, tempMem2, tempMem3, stackMemory;


void machine(int mode, char* inputFilename);
void init(BOFHeader header, Stack* stack);
//executed every machine cycle
int invariantCheck(Stack* stack, address_type pc);


void printMode(BOFFILE bof);

#endif