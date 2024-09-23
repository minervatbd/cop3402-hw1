#include "bof.h"
#include "utilities.h"
#include "machine_types.h"
#include "instruction.h"
#include "stack.h"

address_type generalPurposeRegisters[8];

void machine(int mode, char* inputFilename){
    int pc, hi, lo;
    int invariantCheck;
    //memory mainMemory;
//initalize stack

//read bof file input using bof library functions
    BOFFILE instructions = bof_write_open(inputFilename);


//1) read word in
//2) parse instruction type


//seperate each word into high level variables so that we can perform the appropriate operation (i.e. function from machine.c module)

}

void init(int* pc, int* hi, int* lo, int* inv ){
//read header for proper initalization
   
    return;
}

int checkInvariants(){

}