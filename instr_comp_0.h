#ifndef _INSTR_COMP_0_H
#define _INSTR_COMP_0_H

#include "machine.h"
#include "instruction.h"

// comp functions
extern void add(bin_instr_t i, Stack stack);
extern void subtract(bin_instr_t i, Stack stack);
extern void copyWord(bin_instr_t i, Stack stack);
extern void bitwiseAnd(bin_instr_t i, Stack stack);
extern void bitwiseOr(bin_instr_t i, Stack stack);
extern void bitwiseNor(bin_instr_t i, Stack stack);
extern void bitwiseXor(bin_instr_t i, Stack stack);
extern void loadWord(bin_instr_t i, Stack stack);
extern void storeWord(bin_instr_t i, Stack stack);
extern void storeAddr(bin_instr_t i, Stack stack);
extern void loadWordIndirect(bin_instr_t i, Stack stack);
extern void negate(bin_instr_t i, Stack stack);

#endif
