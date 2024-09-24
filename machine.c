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

void machine(int mode, char* inputFilename)
{

    //read bof file input using bof library functions
    BOFFILE inFile = bof_read_open(inputFilename);
    BOFHeader header = bof_read_header(inFile);

    //initalize stack
    Stack* stack = init(header);


    //1) read word in
    //2) parse instruction type


    //seperate each word into high level variables so that we can perform the appropriate operation (i.e. function from machine.c module)

}

Stack* init(BOFHeader header)
{
    //initalize all registers to 0 (fp and sp are members of the stack struct)
    generalPurposeRegisters = (word_type*) calloc(sizeof(word_type), 6);

    //read header for proper initalization
    Stack* stack = initalizeStack();

    return stack;
}

int checkInvariants()
{

}