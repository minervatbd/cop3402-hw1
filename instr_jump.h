#ifndef _INSTR_JUMP_H
#define _INSTR_JUMP_H

#include "machine.h"
#include "instruction.h"

// jump functions
extern void jumpToAddress(bin_instr_t i);
extern void callSubroutine(bin_instr_t i);
extern void returnFromSubroutine(bin_instr_t i);

#endif