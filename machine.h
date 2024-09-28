#ifndef MACHINE_H
#define MACHINE_H

#include "instruction.h"
#include "machine_types.h"
#include "stack.h"

#define MAX_MEMORY_SIZE 32768 

//our union
extern union mem_u {
word_type words[MAX_MEMORY_SIZE];
uword_type uwords[MAX_MEMORY_SIZE];
bin_instr_t instrs[MAX_MEMORY_SIZE];
} memory;


void machine(int mode, char* inputFilename);
void init(BOFHeader header, Stack* stack);
//executed every machine cycle
int invariantCheck();


void printMode(BOFFILE bof);

#endif