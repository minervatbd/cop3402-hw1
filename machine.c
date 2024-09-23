#include "bof.h"
#include "utilities.h"
#include "machine_types.h"
#include "instruction.h"
#include "stack.h"

//global variables to simulate stack
static word_type* generalPurposeRegisters;
static address_type pc;
static uword_type hi, lo;
static int  invariantCheck;
static union memory mainMemory;

void machine(int mode, char* inputFilename){
//initalize stack
    //init();
//read bof file input using bof library functions
    BOFFILE instructions = bof_write_open(inputFilename);


//1) read word in
//2) parse instruction type


//seperate each word into high level variables so that we can perform the appropriate operation (i.e. function from machine.c module)

}

void init(){
//initalize all registers to 0
generalPurposeRegisters = (address_type*) calloc(sizeof(address_type), 8);
//read header for proper initalization
   
    return;
}

int checkInvariants(){

}