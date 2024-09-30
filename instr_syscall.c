#include <stdio.h>
#include <stdlib.h>
#include "instr_syscall.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

//TODO implement startTracing and stopTracing func
union mem_u tempMemSys;

void exitProgam(bin_instr_t i)
{
    exit(machine_types_sgnExt(i.syscall.offset));
}

void printString(bin_instr_t i, Stack stack)
{
    tempMemSys.words[stack.GPR[SP]] = printf("%s", &tempMemSys.words[stack.GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)]);
}

void printChar(bin_instr_t i,  Stack stack)
{
    tempMemSys.words[stack.GPR[SP]] = fputc(tempMemSys.words[stack.GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)], stdout);
}


void readChar(bin_instr_t i, Stack stack)
{
    tempMemSys.words[stack.GPR[i.syscall.reg] + machine_types_formOffset(i.syscall.offset)] = getc(stdin);
}

void traceInstrPrint(bin_instr_t i, address_type* pc)
{
    fprintf(stdout, "%s%8s\n", TRACE_INSTR_PREFIX, instruction_assembly_form(pc, i));
}

void traceStatePrint(bin_instr_t i)
{

}
