#include <stdlib.h>
#include "machine_types.h"
#include "utilities.h"
#include "machine.h"
#include "regname.h"
#include "stack.h"

Stack* initalizeStack(){
    Stack* myStack = (Stack*) malloc(sizeof(Stack));
    myStack->stackMemory = (union mem_u*) malloc(sizeof(union mem_u));
    myStack->topOffset = 0;
    myStack->maxSize = STACK_HEIGHT;
    return myStack;
}

uword_type ARSize(Stack* stack){
    return stack->GPR[SP] - stack->GPR[FP]; 
}

uword_type stackSize(Stack* stack){
    return ARSize(stack) + stack->topOffset;
}
 
address_type ARTop(Stack* stack){
    return stack->GPR[SP];
}
 
address_type ARBottom(Stack* stack){
    return stack->GPR[FP];
}

//1 for size invariant pass, 2 to indicate stack is full
int stackOkay(Stack* stack){
    if(stackSize(stack) > STACK_HEIGHT)
        return 0;
    else if(stackSize(stack) == STACK_HEIGHT)
        return 2;
    return 1;
}

void push(Stack* stack, word_type val){
    stack->stackMemory->words[stack->GPR[SP]] = val;
    stack->topOffset++;

    return;
}

void pop(Stack* stack){
    stack->stackMemory->words[stack->GPR[SP] - stack->topOffset] = 0;
    stack->topOffset--;

    return;
}

word_type peek(Stack* stack){
    return stack->stackMemory->words[stack->GPR[SP] + stack->topOffset];
}


void addAR(Stack* stack, unsigned int numWords){
    if(!numWords) bail_with_error("Tried to allocate an AR with 0 words");

    if(stackOkay(stack)!=2){
        for(int i= stack->GPR[SP] - stack->topOffset; i < stack->GPR[SP]; i--)
            stack->stackMemory->words[i-1] = stack->stackMemory->words[i];
    } else return;

    stack->GPR[SP]--;
    stack->GPR[FP]--;

    return;
}

void subAR(Stack* stack, unsigned int numWords){
    stack->stackMemory->words[stack->GPR[FP]] = 0;
    for(int i= stack->GPR[SP]; i > stack->GPR[SP] - stack->topOffset; i--)
        stack->stackMemory->words[i+1] = stack->stackMemory->words[i];

    stack->GPR[SP]++;   
    stack->GPR[FP]++; 

    return;
}

/* Unsure if these are needed
extern void allocateSpace(Stack* stack);
extern void deallocate(Stack* stack);
*/