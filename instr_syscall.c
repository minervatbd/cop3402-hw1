#include <stdio.h>
#include <stdlib.h>
#include "instr_syscall.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

//TODO implement startTracing and stopTracing func

void exitProgam(bin_instr_t i)
{
    exit(machine_types_sgnExt(i.syscall.offset));
}

void printString(bin_instr_t i, Stack stack)
{
    memory.words[stack.GPR[SP]] = printf("%s", &memory.words[stack.GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)]);
}

void printChar(bin_instr_t i,  Stack stack)
{
    memory.words[stack.GPR[SP]] = fputc(memory.words[stack.GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)], stdout);
}


void readChar(bin_instr_t i, Stack stack)
{
    memory.words[stack.GPR[i.syscall.reg] + machine_types_formOffset(i.syscall.offset)] = getc(stdin);
}

void startTracing(bin_instr_t i)
{
  
}


void stopTracing(bin_instr_t i)
{

}
