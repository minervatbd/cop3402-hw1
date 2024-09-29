#include "bof.h"
#include "utilities.h"
#include "machine_types.h"
#include "instruction.h"
#include "regname.h"
#include "stack.h"

#include "instr_comp_0.h"
#include "instr_comp_1.h"
#include "instr_immed.h"
#include "instr_jump.h"

//global variables to simulate stack
static address_type pc;
static uword_type hi, lo;
extern union mem_u memory;

void machine(int mode, char* inputFilename)
{
    //read bof file input using bof library functions
    BOFFILE inFile = bof_read_open(inputFilename);

    // -p has been passed, print mode function
    if (mode)
    {
        printMode(inFile);
        return;
    }
    
    // otherwise, normal execution
    else
    {
        // read header
        BOFHeader header = bof_read_header(inFile);
        fseek(inFile.fileptr, 0, SEEK_SET);

        //initalize stack
        Stack* stack = initalizeStack();

        // initialize registers using header data
        init(header, stack);

        //1) read word in
        bin_instr_t instruction = instruction_read(inFile);

        //2) parse instruction type
        instr_type type = instruction_type(instruction);

        // big switch thing for every single type of instruction
        switch (instruction.comp.op) // pretending its a computer instruction to get opcode
        {
            // opcode is 0; comp format instructions pt 1
            case COMP_O:
            switch (instruction.comp.func)
            {
                case NOP_F: // does nothing
                    
                    break;

                case ADD_F: // add
                    add(instruction);
                    break;

                case SUB_F: // subtract
                    subtract(instruction);
                    break;

                case CPW_F: // copy word
                    copyWord(instruction);
                    break;

                case AND_F: // bitwise and
                    bitwiseAnd(instruction);
                    break;

                case BOR_F: // bitwise or
                    bitwiseOr(instruction);
                    break;

                case NOR_F: // bitwise not-or
                    bitwiseNor(instruction);
                    break;

                case XOR_F: // bitwise x-or
                    bitwiseXor(instruction);
                    break;

                case LWR_F: // load word into register
                    loadWord(instruction);
                    break;

                case SWR_F: // store word from register
                    storeWord(instruction);
                    break;

                case SCA_F: // store computed address
                    storeAddr(instruction);
                    break;

                case LWI_F: // load word indirect
                    loadWordIndirect(instruction);
                    break;

                case NEG_F: // negate
                    negate(instruction);
                    break;

                break;

                // error
                default:

                break;
            }
            break;

            // opcode is 1; comp format instructions pt 2 and system calls
            case OTHC_O:
            switch (instruction.comp.func) 
            {
                case LIT_F: // literal (load)
                    literalLoad(instruction);
                    break;

                case ARI_F: // add 
                    addRegImmediate(instruction);
                    break;

                case SRI_F: // subtract register immediate
                    subRegImmediate(instruction);
                    break;

                case MUL_F: // multiply
                    multiply(instruction);
                    break;

                case DIV_F: // divide
                    divide(instruction);
                    break;

                case CFHI_F: // copy from HI
                    copyHI(instruction);
                    break;

                case CFLO_F: // copy from LO
                    copyLO(instruction);
                    break;

                case SLL_F: // shift left logical
                    shiftLeftLogical(instruction);
                    break;

                case SRL_F: // shift right logical
                    shiftRightLogical(instruction);
                    break;

                case JMP_F: // jump
                    jump(instruction);
                    break;

                case CSI_F: // call subroutine indirectly
                    callSubroutineIndirectly(instruction);
                    break;

                case JREL_F: // jump relative to address

                // system calls, another nested switch
                case SYS_F:

                switch (instruction.syscall.code)
                {
                    case exit_sc: // exit

                    break;

                    case print_str_sc: // print string

                    break;

                    case print_char_sc: // print char

                    break;

                    case read_char_sc: // get char

                    break;

                    case start_tracing_sc: // start vm tracing output

                    break;

                    case stop_tracing_sc: // no vm tracing

                    break;

                    // error
                    default:

                    break;
                }
                break;

                // error
                default:

                break;
            }

            break;

            // all the immediate instructions
            case ADDI_O: // add immediate
                addImmed(instruction);
                break;
            
            case ANDI_O: // bitwise and immediate
                andImmed(instruction);
                break;
            
            case BORI_O: // bitwise or immediate
                borImmed(instruction);
                break;
            
            case NORI_O: // bitwise not-or immediate
                norImmed(instruction);
                break;

            case XORI_O: // bitwise x-or immediate
                xorImmed(instruction);
                break;

            case BEQ_O: // branch on equal
                branchOnEqual(instruction);
                break;

            case BGEZ_O: // branch >= 0
                branchGreaterEqualThanZero(instruction);
                break;

            case BGTZ_O: // branch > 0
                branchGreaterThanZero(instruction);
                break;

            case BLEZ_O: // branch <= 0
                branchLessEqualThanZero(instruction);
                break;

            case BLTZ_O: // branch < 0
                branchLessThanZero(instruction);
                break;

            case BNE_O: // branch not equal
                branchNotEqual(instruction);
                break;

            // jump format instructions
            case JMPA_O: // jump to given address
                jumpToAddress(instruction);
                break;

            case CALL_O: // call subroutine
                callSubroutine(instruction);
                break;

            case RTN_O: // return from subroutine
                returnFromSubroutine(instruction);
                break;

            // error
            default:
            
            break;
        }
    }
}

void init(BOFHeader header, Stack* stack)
{
    // set $gp to header data start address 
    stack->GPR[GP] = header.data_start_address;

    // set $sp and $fp to bottom of stack address, must be strictly greater than data start address
    stack->GPR[SP] = header.stack_bottom_addr;
    stack->GPR[FP] = header.stack_bottom_addr;

    // set pc to text address start
    pc = header.text_start_address;

    return;
}

int checkInvariants()
{

}

// reads instructions from bof file and prints them properly
void printMode(BOFFILE bof)
{
    // read header
    BOFHeader header = bof_read_header(bof);

    //reset file pointer to instruction start
    word_type pc = header.text_start_address;
    //fseek(bof.fileptr, pc + sizeof(header), SEEK_SET);

    printf("Address Instruction\n");

    while (!bof_at_eof(bof))
    {
        printf("%d: %s\n", pc, instruction_assembly_form((address_type) pc, instruction_read(bof)));
        pc++;
    }

    return;
}


int invariantCheck(Stack* stack, address_type pc){
    //evaluate invariant conditions and print error -> return 0 if conidtion is violated, else print 1
    if(stack->GPR[GP] < 0){
        sprintf(stderr, "\nInvariant violated. Globals pointer cannot be less than zero.\n");
        return 0;
    }

    if(stack->GPR[GP] >= stack->GPR[SP]){
        sprintf(stderr, "\nInvariant violated. Globals pointer cannot be greater than the stack pointer.\n");
        return 0;
    }

    if(stack->GPR[SP] > stack->GPR[FP]){
        sprintf(stderr, "\nInvariant violated. Stack pointer cannot be greater than the frame pointer.\n");
        return 0;
    }

    if(stack->GPR[FP] >= MAX_MEMORY_SIZE){
        sprintf(stderr, "\nInvariant violated. Frame pointer cannot reach maximum memory address.\n");
        return 0;
    }

    if(pc < 0){
        sprintf(stderr, "\nInvariant violated. Program counter must be a nonzero address.\n");
        return 0;
    }

    if(pc >= MAX_MEMORY_SIZE){
        sprintf(stderr, "\nInvariant violated. Program counter must not exceed maximum memory address.\n");
        return 0;
    }

    return 1;
}