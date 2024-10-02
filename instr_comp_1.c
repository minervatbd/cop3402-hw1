#include "instr_comp_1.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

void literalLoad(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] =  machine_types_sgnExt(i.othc.arg);
}

void addRegImmediate(bin_instr_t i, Stack* stack)
{
    stack->GPR[i.othc.reg] = (stack->GPR[i.othc.reg] + machine_types_sgnExt(i.othc.arg));
}

void subRegImmediate(bin_instr_t i, Stack* stack)
{
    stack->GPR[i.othc.reg] = (stack->GPR[i.othc.reg] - machine_types_sgnExt(i.othc.arg));
}

void multiply(bin_instr_t i, Stack* stack, uword_type* lo, uword_type* hi)
{
     long temp = (stack->stackMemory->words[stack->GPR[SP]] * stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)]);
    
    //get least significant bits
    *lo = temp ^ 0x00000000;

    //get most significant bits
    *hi = temp >> 32;
}

void divide(bin_instr_t i, Stack* stack, uword_type* lo, uword_type* hi)
{
    *hi = stack->stackMemory->words[stack->GPR[SP]] % stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
    *lo = stack->stackMemory->words[stack->GPR[SP]] / stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
}

void copyHI(bin_instr_t i, Stack* stack, uword_type* hi)
{
    stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = *hi;
}

void copyLO(bin_instr_t i, Stack* stack, uword_type* lo)
{
    stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = *lo;

}

void shiftLeftLogical(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = stack->stackMemory->uwords[stack->GPR[SP]] << i.othc.arg;
}

void shiftRightLogical(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = stack->stackMemory->uwords[stack->GPR[SP]] >> i.othc.arg;

}

void jump(bin_instr_t i, Stack* stack, address_type* pc)
{
    *pc = stack->stackMemory->uwords[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];    
}

void jumpRelative(bin_instr_t i,  address_type* pc){
    *pc = (*pc - 1) + i.othc.offset;
}

void callSubroutineIndirectly(bin_instr_t i, Stack* stack, address_type* pc)
{
    stack->GPR[RA] = *pc;
    *pc = stack->stackMemory->words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
}
