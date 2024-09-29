#include "instr_comp_1.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

// TEMP VARS TODO
union mem_u tempMem2;

void literalLoad(bin_instr_t i, Stack* stack)
{
    tempMem2.words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] =  machine_types_sgnExt(i.othc.arg);
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
    //get most significant bit

    //get least significant bit
    *lo = (tempMem2.words[stack->GPR[SP]] * tempMem2.words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] & 1);

}

void divide(bin_instr_t i, Stack* stack, uword_type* lo, uword_type* hi)
{
    *hi = tempMem2.words[stack->GPR[SP]] % tempMem2.words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
    *lo = tempMem2.words[stack->GPR[SP]] / tempMem2.words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
}

void copyHI(bin_instr_t i, Stack* stack, uword_type* hi)
{
    tempMem2.words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = *hi;
}

void copyLO(bin_instr_t i, Stack* stack, uword_type* lo)
{
    tempMem2.words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = *lo;

}

void shiftLeftLogical(bin_instr_t i, Stack* stack)
{
    tempMem2.uwords[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = tempMem2.uwords[stack->GPR[SP]] << i.othc.arg;
}

void shiftRightLogical(bin_instr_t i, Stack* stack)
{
    tempMem2.uwords[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = tempMem2.uwords[stack->GPR[SP]] >> i.othc.arg;

}

void jump(bin_instr_t i, Stack* stack, address_type* pc)
{
    *pc = tempMem2.uwords[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];    
}

void callSubroutineIndirectly(bin_instr_t i, Stack* stack, address_type* pc)
{
    stack->GPR[RA] = *pc;
    *pc = tempMem2.words[stack->GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
}
