#ifndef _INSTR_SYSCALL_H
#define _INSTR_SYSCALL_H

#include "machine.h"
#include "instruction.h"

// comp format functions
extern void exitProgam(bin_instr_t i);
extern void printString(bin_instr_t i, Stack stack);
extern void printChar(bin_instr_t i, Stack stack);
extern void readChar(bin_instr_t i, Stack stack);
extern void startTracing(bin_instr_t i);
extern void stopTracing(bin_instr_t i);

#endif
