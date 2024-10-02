#ifndef _INSTR_SYSCALL_H
#define _INSTR_SYSCALL_H

#include "machine.h"
#include "instruction.h"

#define TRACE_INSTR_PREFIX "==>"
#define PC_PRINT "PC"
#define HI_PRINT "HI"
#define LO_PRINT "LO"
#define GPR_PRINT "GPR"

// comp format functions
extern void exitProgam(bin_instr_t i);
extern void printString(bin_instr_t i, Stack* stack);
extern void printChar(bin_instr_t i, Stack* stack);
extern void readChar(bin_instr_t i, Stack* stack);
extern int startTrace();
extern int stopTrace();
extern void traceInstrPrint(bin_instr_t i, address_type* pc);
extern void traceStatePrint(address_type* pc, uword_type* hi, uword_type* lo, Stack* stack);
static int resetLen();
static int stdPrint(char** currentOut, int len, int adr, word_type instr);

#endif
