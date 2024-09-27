#ifndef _INSTR_IMMED_H
#define _INSTR_IMMED_H

#include "machine.h"
#include "instruction.h"

// immediate format functions
extern void addImmed(bin_instr_t i);
extern void andImmed(bin_instr_t i);
extern void borImmed(bin_instr_t i);
extern void norImmed(bin_instr_t i);
extern void xorImmed(bin_instr_t i);
extern void branchOnEqual(bin_instr_t i);
extern void branchGreaterEqualThanZero(bin_instr_t i);
extern void branchGreaterThanZero(bin_instr_t i);
extern void branchLessEqualThanZero(bin_instr_t i);
extern void branchLessThanZero(bin_instr_t i);
extern void branchNotEqual(bin_instr_t i);

#endif