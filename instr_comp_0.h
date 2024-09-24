#include "machine.h"
#include "instruction.h"

// comp functions
extern void add(comp_instr_t i);
extern void subtract(comp_instr_t i);
extern void copyWord(comp_instr_t i);
extern void bitwiseAnd(comp_instr_t i);
extern void bitwiseOr(comp_instr_t i);
extern void bitwiseNor(comp_instr_t i);
extern void bitwiseXor(comp_instr_t i);
extern void loadWord(comp_instr_t i);
extern void storeWord(comp_instr_t i);
extern void storeAddr(comp_instr_t i);
extern void loadWordIndirect(comp_instr_t i);
extern void negate(comp_instr_t i);