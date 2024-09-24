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
    bin_instr_t instruction = instruction_read(inFile);

    //2) parse instruction type
    instr_type type = instruction_type(instruction);

    // big switch thing for every single type of instruction
    switch (instruction.comp.op) 
    {
        // opcode is 0; comp format instructions pt 1
        case COMP_O:
        
        break;

        // opcode is 1; comp format instructions pt 2 and system calls
        case OTHC_O:

        break;

        // all the immediate instructions
        case ADDI_O: // add immediate
        
        break;
        
        case ANDI_O: // bitwise and immediate
        
        break;
        
        case BORI_O: // bitwise or immediate
        
        break;
        
        case NORI_O: // bitwise not-or immediate
        
        break;
        
        case XORI_O: // bitwise x-or immediate
        
        break;
        
        case BEQ_O: // branch on equal
        
        break;
        
        case BGEZ_O: // branch >= 0
        
        break;
        
        case BGTZ_O: // branch > 0
        
        break;
        
        case BLEZ_O: // branch <= 0
        
        break;
        
        case BLTZ_O: // branch < 0
        
        break;
        
        case BNE_O: // branch not equal
        
        break;
        
        // jump format instructions
        case JMPA_O: // jump to given address
        
        break;
        
        case CALL_O: // call subroutine
        
        break;
        
        case RTN_O: // return from subroutine
        
        break;
        
        // error
        default:
        
        break;
    }
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