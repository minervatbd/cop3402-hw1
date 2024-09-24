#include "machine_types.h"

#define STACK_HEIGHT 4096

//stack that grows upward (as opposed to downward example provided in class)
typedef struct{
    address_type fp;
    address_type sp;
    int topOffset;
    word_type stackMemory[STACK_HEIGHT];
} Stack;

extern Stack* initalizeStack();

//return data relevant to stack and AR contents
extern uword_type ARSize(Stack* stack);
extern uword_type stackSize(Stack* stack);
extern address_type ARTop(Stack* stack);
extern address_type ARBottom(Stack* stack);

//check invariant and if stack is full
extern int stackOkay(Stack* stack);

//stack operations
extern void push(Stack* stack, word_type val);
extern void pop(Stack* stack);
extern word_type peek(Stack* stack);

//AR operations
extern void addAR(Stack* stack, word_type AR);
extern void subAR(Stack* stack);
extern void allocateSpace(Stack* stack);
extern void deallocate(Stack* stack);
