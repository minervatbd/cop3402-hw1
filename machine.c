#include "bof.h"
#include "utilities.h"
#include "machine_types.h"
#include "instruction.h"
#include "stack.h"

//global variables to simulate stack
static word_type gp; // globals pointer register
static word_type ra; // return address register
static word_type* generalRegisters; // other registers (r3-r6)
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
    Stack* stack = initalizeStack();

    // initialize registers using header data
    init(header, stack);

    //1) read word in
    //2) parse instruction type


    //seperate each word into high level variables so that we can perform the appropriate operation (i.e. function from machine.c module)

}

void init(BOFHeader header, Stack* stack)
{
    // initalize general registers to 0
    generalRegisters = (word_type*) calloc(sizeof(word_type), 4);

    for (int c = 0; c < 4; c++)
        generalRegisters[c] = 0;

    // set $gp to header data start address 
    gp = header.data_start_address;

    // set $sp and $fp to bottom of stack address, must be strictly greater than data start address
    stack->sp = header.stack_bottom_addr;
    stack->fp = header.stack_bottom_addr;

    // set pc to text address start
    pc = header.text_start_address;

    return;
}

int checkInvariants()
{

}