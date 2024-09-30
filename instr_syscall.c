#include <stdio.h>
#include <stdlib.h>
#include "instr_syscall.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"
#include "utilities.h"

//TODO implement startTracing and stopTracing func

void exitProgam(bin_instr_t i)
{
    exit(machine_types_sgnExt(i.syscall.offset));
}

void printString(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[SP]] = printf("%s", stack->stackMemory->words[stack->GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)]);
}

void printChar(bin_instr_t i,  Stack* stack)
{
    stack->stackMemory->words[stack->GPR[SP]] = fputc(stack->stackMemory->words[stack->GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)], stdout);
}


void readChar(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.syscall.reg] + machine_types_formOffset(i.syscall.offset)] = getc(stdin);
}

int startTrace(){
    return 1;
}

int stopTrace(){
    return 0;
}

void traceInstrPrint(bin_instr_t i, address_type* pc)
{
    fprintf(stdout, "\t%d:%s%8s\n", *pc, TRACE_INSTR_PREFIX, instruction_assembly_form(*pc, i));
}

void traceStatePrint(address_type* pc, uword_type* hi, uword_type* lo, Stack* stack)
{
    fprintf(stdout, "%8s: %d\n", PC_PRINT, *pc);
    for(int c = 0; c <= RA; c++)
    {
        if (c == 5)
            newline(stdout);
        
        fprintf(stdout, "%s[%s]: %-6d", GPR_PRINT, regname_get(c), stack->GPR[c]);
    }
    newline(stdout);
    
    fprintf(stdout, "");
    // data section TODO
}
