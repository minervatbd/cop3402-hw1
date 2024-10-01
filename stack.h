#ifndef STACK_H
#define STACK_H

#include "machine_types.h"

#define STACK_HEIGHT 4096

//stack struct
typedef struct{
    int topOffset;
    union mem_u* stackMemory;
    int maxSize; 
    address_type GPR[8];
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
extern void addAR(Stack* stack, unsigned int numWords);
extern void subAR(Stack* stack, unsigned int numWords);
extern void allocateSpace(Stack* stack);
extern void deallocate(Stack* stack);

#endif