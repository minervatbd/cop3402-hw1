#ifndef _INSTR_COMP_1_H
#define _INSTR_COMP_1_H

#include "machine.h"
#include "instruction.h"

// comp format functions
extern void literalLoad(bin_instr_t i, Stack* stack);
extern void addRegImmediate(bin_instr_t i, Stack* stack);
extern void subRegImmediate(bin_instr_t i, Stack* stack);
extern void multiply(bin_instr_t i, Stack* stack, uword_type* lo, uword_type* hi);
extern void divide(bin_instr_t i, Stack* stack, uword_type* lo, uword_type* hi);
extern void copyHI(bin_instr_t i, Stack* stack, uword_type* hi);
extern void copyLO(bin_instr_t i, Stack* stack, uword_type* lo);
extern void shiftLeftLogical(bin_instr_t i, Stack* stack);
extern void shiftRightLogical(bin_instr_t i, Stack* stack);
extern void jump(bin_instr_t i, Stack* stack, address_type* pc);
extern void callSubroutineIndirectly(bin_instr_t i, Stack* stack, address_type* pc);

#endif
