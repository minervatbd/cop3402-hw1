#ifndef _INSTR_IMMED_H
#define _INSTR_IMMED_H

#include "machine.h"
#include "instruction.h"

// immediate format functions
extern void addImmed(bin_instr_t i, Stack* stack);
extern void andImmed(bin_instr_t i, Stack* stack);
extern void borImmed(bin_instr_t i, Stack* stack);
extern void norImmed(bin_instr_t i, Stack* stack);
extern void xorImmed(bin_instr_t i, Stack* stack);
extern void branchOnEqual(bin_instr_t i, Stack* stack, address_type* pc);
extern void branchGreaterEqualThanZero(bin_instr_t i, Stack* stack, address_type* pc);
extern void branchGreaterThanZero(bin_instr_t i, Stack* stack, address_type* pc);
extern void branchLessEqualThanZero(bin_instr_t i, Stack* stack, address_type* pc);
extern void branchLessThanZero(bin_instr_t i, Stack* stack, address_type* pc);
extern void branchNotEqual(bin_instr_t i, Stack* stack, address_type* pc);

#endif
