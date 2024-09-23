#include "machine_types.h"

#define STACK_HEIGHT 4096

extern void initalizeStack();

//return data relevant to stack and AR contents
extern uword_type ARSize();
extern uword_type stackSize();
extern address_type ARTop();
extern address_type ARBottom();

//check invariant and if stack is full
extern int stackOkay();

//stack operations
extern void push();
extern void pop();
extern void peek();

//AR operations
extern void beginAR();
extern void endAR();
