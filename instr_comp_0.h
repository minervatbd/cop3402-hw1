#include "machine.h"
#include "instruction.h"

// comp functions
extern void add(bin_instr_t i);
extern void subtract(bin_instr_t i);
extern void copyWord(bin_instr_t i);
extern void bitwiseAnd(bin_instr_t i);
extern void bitwiseOr(bin_instr_t i);
extern void bitwiseNor(bin_instr_t i);
extern void bitwiseXor(bin_instr_t i);
extern void loadWord(bin_instr_t i);
extern void storeWord(bin_instr_t i);
extern void storeAddr(bin_instr_t i);
extern void loadWordIndirect(bin_instr_t i);
extern void negate(bin_instr_t i);