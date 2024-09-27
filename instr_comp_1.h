#ifndef _INSTR_COMP_1_H
#define _INSTR_COMP_1_H

#include "machine.h"
#include "instruction.h"

// comp format functions
extern void literalLoad(bin_instr_t i);
extern void addRegImmediate(bin_instr_t i);
extern void subRegImmediate(bin_instr_t i);
extern void multiply(bin_instr_t i);
extern void divide(bin_instr_t i);
extern void copyHI(bin_instr_t i);
extern void copyLO(bin_instr_t i);
extern void shiftLeftLogical(bin_instr_t i);
extern void shiftRightLogical(bin_instr_t i);
extern void jump(bin_instr_t i);
extern void callSubroutineIndirectly(bin_instr_t i);

#endif