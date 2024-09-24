#include "machine.h"
#include "instruction.h"

// comp format functions
extern void literalLoad(comp_instr_t i);
extern void addRegImmediate(comp_instr_t i);
extern void subRegImmediate(comp_instr_t i);
extern void multiply(comp_instr_t i);
extern void divide(comp_instr_t i);
extern void copyHI(comp_instr_t i);
extern void copyLO(comp_instr_t i);
extern void shiftLeftLogical(comp_instr_t i);
extern void shiftRightLogical(comp_instr_t i);
extern void jump(comp_instr_t i);
extern void callSubroutineIndirectly(comp_instr_t i);