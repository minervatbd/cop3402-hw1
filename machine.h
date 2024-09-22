#include "instruction.h"
#include "machine_types.h"

//macros
#define MAX_MEMORY_SIZE 32768

//structs
static union mem_u {
word_type words[MAX_MEMORY_SIZE];
uword_type uwords[MAX_MEMORY_SIZE];
bin_instr_t instrs[MAX_MEMORY_SIZE];
} memory;

void machine(int mode, char* inputFilename);