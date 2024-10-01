#include <string.h>

#include "bof.h"
#include "utilities.h"
#include "machine_types.h"
#include "instruction.h"
#include "regname.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#include "instr_comp_0.h"
#include "instr_comp_1.h"
#include "instr_immed.h"
#include "instr_jump.h"
#include "instr_syscall.h"


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

        //other variables to simulate svm
        address_type pc;
        uword_type hi, lo;

        //initalize stack
        Stack* stack = initalizeStack();

        // initialize registers using header data
        init(header, stack, &pc, &hi, &lo);

        //read instructions into dedicated memory
        unsigned int numInstrs = header.text_length;
        bin_instr_t* instructions = (bin_instr_t*) malloc(sizeof(bin_instr_t) * numInstrs);
        for(int i= 0; i < numInstrs; i++)
            instructions[i] = instruction_read(inFile);  
        
        //read data into memory
        for(int j = stack->GPR[GP]; j < stack->GPR[GP] + header.data_length; j++)
            stack->stackMemory->words[j] = bof_read_word(inFile);

        //initial trace
        traceStatePrint(&pc, &hi, &lo, stack);

        //beign instruction cycle and declare vars needed for invariant check and tracing
        bin_instr_t currInstr;
        //tracing is on by default
        int tracingBool = 1;

        while(invariantCheck(stack, pc)){
            //fetch instruction
            currInstr = instructions[pc];
            //trace instruction 
            if(tracingBool)
                traceInstrPrint(currInstr, &pc);

            //update pc
            pc++;
        
            // big switch thing for every single type of instruction
            switch (currInstr.comp.op) // pretending its a computer instruction to get opcode
            {
                // opcode is 0; comp format instructions pt 1
                case COMP_O:
                switch (currInstr.comp.func)
                {
                    case NOP_F: // does nothing
                        
                        break;

                    case ADD_F: // add
                        add(currInstr, stack);
                        break;

                    case SUB_F: // subtract
                        subtract(currInstr, stack);
                        break;

                    case CPW_F: // copy word
                        copyWord(currInstr, stack);
                        break;

                    case AND_F: // bitwise and
                        bitwiseAnd(currInstr, stack);
                        break;

                    case BOR_F: // bitwise or
                        bitwiseOr(currInstr, stack);
                        break;

                    case NOR_F: // bitwise not-or
                        bitwiseNor(currInstr, stack);
                        break;

                    case XOR_F: // bitwise x-or
                        bitwiseXor(currInstr, stack);
                        break;

                    case LWR_F: // load word into register
                        loadWord(currInstr, stack);
                        break;

                    case SWR_F: // store word from register
                        storeWord(currInstr, stack);
                        break;

                    case SCA_F: // store computed address
                        storeAddr(currInstr, stack);
                        break;

                    case LWI_F: // load word indirect
                        loadWordIndirect(currInstr, stack);
                        break;

                    case NEG_F: // negate
                        negate(currInstr, stack);
                        break;

                    break;

                    // error
                    default:

                    break;
                }
                break;

                // opcode is 1; comp format instructions pt 2 and system calls
                case OTHC_O:
                switch (currInstr.comp.func) 
                {
                    case LIT_F: // literal (load)
                        literalLoad(currInstr, stack);
                        break;

                    case ARI_F: // add 
                        addRegImmediate(currInstr, stack);
                        break;

                    case SRI_F: // subtract register immediate
                        subRegImmediate(currInstr, stack);
                        break;

                    case MUL_F: // multiply
                        multiply(currInstr, stack, &lo, &hi);
                        break;

                    case DIV_F: // divide
                        divide(currInstr, stack, &lo, &hi);
                        break;

                    case CFHI_F: // copy from HI
                        copyHI(currInstr, stack, &hi);
                        break;

                    case CFLO_F: // copy from LO
                        copyLO(currInstr, stack, &lo);
                        break;

                    case SLL_F: // shift left logical
                        shiftLeftLogical(currInstr, stack);
                        break;

                    case SRL_F: // shift right logical
                        shiftRightLogical(currInstr, stack);
                        break;

                    case JMP_F: // jump
                        jump(currInstr, stack, &pc);
                        break;

                    case CSI_F: // call subroutine indirectly
                        callSubroutineIndirectly(currInstr, stack, &pc);
                        break;

                    case JREL_F: // jump relative to address
                        jumpRelative(currInstr, &pc);
                    // system calls, another nested switch
                    case SYS_F:
                        switch (currInstr.syscall.code)
                        {
                            case exit_sc: // exit
                                exitProgam(currInstr);
                            break;

                            case print_str_sc: // print string
                                printString(currInstr, stack);
                            break;

                            case print_char_sc: // print char
                                printChar(currInstr, stack);
                            break;

                            case read_char_sc: // get char
                                readChar(currInstr, stack);
                            break;

                            case start_tracing_sc: // start vm tracing output
                                tracingBool = startTrace();
                            break;

                            case stop_tracing_sc: // no vm tracing
                                tracingBool = stopTrace();
                            break;

                            // error
                            default:
                                fprintf(stderr, "\n *Error*: could not parse instruction correctly (syscall op code)\n");
                            break;
                        }
                    break;

                    // error
                    default:
                        fprintf(stderr, "\n *Error*: could not parse instruction correctly (comp function code)\n");
                    break;
                }

                break;

                // all the immediate instructions
                case ADDI_O: // add immediate
                    addImmed(currInstr, stack);
                    break;
                
                case ANDI_O: // bitwise and immediate
                    andImmed(currInstr, stack);
                    break;
                
                case BORI_O: // bitwise or immediate
                    borImmed(currInstr, stack);
                    break;
                
                case NORI_O: // bitwise not-or immediate
                    norImmed(currInstr, stack);
                    break;

                case XORI_O: // bitwise x-or immediate
                    xorImmed(currInstr, stack);
                    break;

                case BEQ_O: // branch on equal
                    branchOnEqual(currInstr, stack, &pc);
                    break;

                case BGEZ_O: // branch >= 0
                    branchGreaterEqualThanZero(currInstr, stack, &pc);
                    break;

                case BGTZ_O: // branch > 0
                    branchGreaterThanZero(currInstr, stack, &pc);
                    break;

                case BLEZ_O: // branch <= 0
                    branchLessEqualThanZero(currInstr, stack, &pc);
                    break;

                case BLTZ_O: // branch < 0
                    branchLessThanZero(currInstr, stack, &pc);
                    break;

                case BNE_O: // branch not equal
                    branchNotEqual(currInstr, stack, &pc);
                    break;

                // jump format instructions
                case JMPA_O: // jump to given address
                    jumpToAddress(currInstr, &pc);
                    break;

                case CALL_O: // call subroutine
                    callSubroutine(currInstr, stack, &pc);
                    break;

                case RTN_O: // return from subroutine
                    returnFromSubroutine(currInstr, stack, &pc);
                    break;

                // error
                default:
                    fprintf(stderr, "\n *Error*: could not parse instruction correctly (j/i-type op code)\n");
                break;
            }

            //trace machine state
            if(tracingBool)
                traceStatePrint(&pc, &hi, &lo, stack);
        }
    }
}

void init(BOFHeader header, Stack* stack, address_type* pc, uword_type* hi, uword_type* lo)
{
    // set $gp to header data start address (-1 because of zero indexing)
    stack->GPR[GP] = header.data_start_address;

    // set $sp and $fp to bottom of stack address, must be strictly greater than data start address (-1 because of zero indexing)
    stack->GPR[SP] = header.stack_bottom_addr;
    stack->GPR[FP] = header.stack_bottom_addr;

    // set pc to text address start, hi/lo to zero
    *pc = header.text_start_address;
    *hi = 0, *lo = 0;

    return;
}

// reads instructions from bof file and prints them properly
void printMode(BOFFILE bof)
{
    // read header
    BOFHeader header = bof_read_header(bof);
    word_type pc = header.text_start_address;

    instruction_print_table_heading(stdout);

    // printing instructions
    while (pc < header.text_start_address + header.text_length)
    {
        printf("%6d: %s\n", pc, instruction_assembly_form((address_type) pc, instruction_read(bof)));
        pc++;
    }

    //printf("\n\nData section\n\n");

    // jump to data start address
    pc = header.data_start_address;

    // current word
    word_type word;

    // current line length
    int len = 0;

    // if a zero is printed, dont print any zeros after that.
    int printNextZero = 1;

    char* currentOut = (char*) malloc(sizeof(char)*MAX_DATA_LINE_LENGTH*2);

    // data section start
    while (pc < header.data_start_address + header.data_length)
    {
        word = bof_read_word(bof);

        if (word == 0 && printNextZero == 1)
        {
            sprintf(currentOut, "%8d: %d", pc, word);
            len += strlen(currentOut);
            printf("%s", currentOut);
            printNextZero = 0;
        }
            
        else if (word == 0 && printNextZero == 0)
        {
            sprintf(currentOut, DATA_SEPARATOR);
            len += strlen(currentOut);
            printf("%s", currentOut);
            printNextZero = -1;
        }

        else if (strcmp(currentOut, DATA_SEPARATOR) == 0)
        {
            continue;
        }

        else if (word != 0)
        {
            sprintf(currentOut, "%8d: %d", pc, word);
            len += strlen(currentOut);
            printf("%s", currentOut);
            printNextZero = 1;
        }

        if (len > MAX_DATA_LINE_LENGTH)
        {
            newline(stdout);
            len = 0;
        }

        pc++;
    }

    if (printNextZero)
    {
        sprintf(currentOut, "%8d: %d", pc, 0);
        len += strlen(currentOut);
        printf("%s", currentOut);
    }

    if (len > MAX_DATA_LINE_LENGTH)
        newline(stdout);

    printf("%s", DATA_SEPARATOR);

    //printf("%s\n", currentOut);

    newline(stdout);

    free(currentOut);

    return;
}


int invariantCheck(Stack* stack, address_type pc){
    //evaluate invariant conditions and print error -> return 0 if conidtion is violated, else print 1
    if(stack->GPR[GP] < 0){
        fprintf(stderr, "\nInvariant violated. Globals pointer cannot be less than zero.\n");
        return 0;
    }

    if(stack->GPR[GP] >= stack->GPR[SP]){
        fprintf(stderr, "\nInvariant violated. Globals pointer cannot be greater than the stack pointer.\n");
        return 0;
    }

    if(stack->GPR[SP] > stack->GPR[FP]){
        fprintf(stderr, "\nInvariant violated. Stack pointer cannot be greater than the frame pointer.\n");
        return 0;
    }

    if(stack->GPR[FP] >= MAX_MEMORY_SIZE){
        fprintf(stderr, "\nInvariant violated. Frame pointer cannot reach maximum memory address.\n");
        return 0;
    }

    if(pc < 0){
        fprintf(stderr, "\nInvariant violated. Program counter must be a nonzero address.\n");
        return 0;
    }

    if(pc >= MAX_MEMORY_SIZE){
        fprintf(stderr, "\nInvariant violated. Program counter must not exceed maximum memory address.\n");
        return 0;
    }

    return 1;
}