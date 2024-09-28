#include "instr_jump.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

void jumpToAddress(bin_instr_t i)
{
    pc = machine_types_formAddress(pc-1, i.jump.addr);
}

void callSubroutine(bin_instr_t i, Stack stack)
{
    stack.GPR[RA] = pc;
    pc = machine_types_formAddress(pc-1, i.jump.addr);
}

void returnFromSubroutine(bin_instr_t i, Stack stack)
{
    pc = stack.GPR[RA];
}
