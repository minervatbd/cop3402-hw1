#ifndef MACHINE_H
#define MACHINE_H

#include "instruction.h"
#include "machine_types.h"
#include "stack.h"

//macros for memory and data outputs
#define MAX_MEMORY_SIZE 65536 
#define MAX_DATA_LINE_LENGTH 80
#define MAX_DATA_LINE_LENGTH_P 59
#define DATA_SEPARATOR "        ...     "

//main memory representation
extern union mem_u {
word_type words[MAX_MEMORY_SIZE];
uword_type uwords[MAX_MEMORY_SIZE];
}stackMemory;


void machine(int mode, char* inputFilename);
void init(BOFHeader header, Stack* stack, address_type* pc, uword_type* hi, uword_type* lo);

//executed every machine cycle
int invariantCheck(Stack* stack, address_type pc);


void printMode(BOFFILE bof);

#endif