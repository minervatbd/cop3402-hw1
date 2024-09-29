#include "instr_comp_1.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

void literalLoad(bin_instr_t i, Stack stack)
{
    memory.words[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] =  machine_types_sgnExt(i.othc.arg);
}

void addRegImmediate(bin_instr_t i, Stack stack)
{
    stack.GPR[i.othc.reg] = (stack.GPR[i.othc.reg] + machine_types_sgnExt(i.othc.arg));
}

void subRegImmediate(bin_instr_t i, Stack stack)
{
    stack.GPR[i.othc.reg] = (stack.GPR[i.othc.reg] - machine_types_sgnExt(i.othc.arg));
}

void multiply(bin_instr_t i, Stack stack)
{
    //get most significant bit

    //get least significant bit
    lo = (memory.words[stack.GPR[SP]] * memory.words[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] & 1);

}

void divide(bin_instr_t i, Stack stack)
{
    hi = memory.words[stack.GPR[SP]] % memory.words[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
    lo = memory.words[stack.GPR[SP]] / memory.words[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
}

void copyHI(bin_instr_t i, Stack stack)
{
    memory.words[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = hi;
}

void copyLO(bin_instr_t i, Stack stack)
{
    memory.words[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = lo;

}

void shiftLeftLogical(bin_instr_t i, Stack stack)
{
    memory.uwords[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = memory.uwords[stack.GPR[SP]] << i.othc.arg;
}

void shiftRightLogical(bin_instr_t i, Stack stack)
{
    memory.uwords[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)] = memory.uwords[stack.GPR[SP]] >> i.othc.arg;

}

void jump(bin_instr_t i, Stack stack)
{
    pc = memory.uwords[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];    
}

void callSubroutineIndirectly(bin_instr_t i, Stack stack)
{
    stack.GPR[RA] = pc;
    pc = memory.words[stack.GPR[i.othc.reg] + machine_types_formOffset(i.othc.offset)];
}
