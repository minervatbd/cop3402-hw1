#include "machine.h"
#include "instruction.h"

// jump functions
extern void jumpToAddress(jump_instr_t i);
extern void callSubroutine(jump_instr_t i);
extern void returnFromSubroutine(jump_instr_t i);