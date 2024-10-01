#include "instr_jump.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

void jumpToAddress(bin_instr_t i, address_type* pc)
{
    *pc = machine_types_formAddress(*pc-1, i.jump.addr);
}

void callSubroutine(bin_instr_t i, Stack* stack, address_type* pc)
{
    stack->GPR[RA] = *pc;
    *pc = machine_types_formAddress(*pc - 1, i.jump.addr);
}

void returnFromSubroutine(bin_instr_t i, Stack* stack, address_type* pc)
{
    *pc = stack->GPR[RA];
}
