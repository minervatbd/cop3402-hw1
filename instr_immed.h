#include "machine.h"
#include "instruction.h"

// immediate format functions
extern void addImmed(immed_instr_t i);
extern void andImmed(immed_instr_t i);
extern void borImmed(immed_instr_t i);
extern void norImmed(immed_instr_t i);
extern void xorImmed(immed_instr_t i);
extern void branchOnEqual(immed_instr_t i);
extern void branchGreaterEqualThanZero(immed_instr_t i);
extern void branchGreaterThanZero(immed_instr_t i);
extern void branchLessEqualThanZero(immed_instr_t i);
extern void branchLessThanZero(immed_instr_t i);
extern void brnachNotEqual(immed_instr_t i);