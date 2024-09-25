#include "machine_types.h"
#include "regname.h"
#include "stack.h"

Stack* initalizeStack(){
    Stack* myStack = (Stack*) malloc(sizeof(Stack));
    myStack->topOffset = 0;
    
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

//if sp > fp and !sp> max size, 1 for invariant pass, 2 to indicate stack is full
int stackOkay(Stack* stack){
    if(stack->GPR[SP] <= stack->GPR[FP])
        return 0;
    if(stack->GPR[SP] > STACK_HEIGHT)
        return 0;
    else if(stack->GPR[SP] == STACK_HEIGHT)
        return 2;
    return 1;
}

void push(Stack* stack, word_type val){
    stack->stackMemory[stack->GPR[SP] + stack->topOffset] = val;
    stack->topOffset++;

    return;
}

void pop(Stack* stack){
    stack->stackMemory[stack->GPR[SP] + stack->topOffset] = 0;
    stack->topOffset--;

    return;
}

word_type peek(Stack* stack){
    return stack->stackMemory[stack->GPR[SP] + stack->topOffset];
}


void addAR(Stack* stack, word_type AR){
    stack->stackMemory[stack->GPR[SP]-1] = AR;
    for(int i= stack->GPR[SP] + stack->topOffset; i > stack->GPR[SP]; i--)
        stack->stackMemory[i+1] = stack->stackMemory[i];
    
    stack->GPR[SP]++;

    return;
}

void subAR(Stack* stack){
    stack->stackMemory[stack->GPR[SP]-1] = 0;
    for(int i= stack->GPR[SP] + stack->topOffset; i > stack->GPR[SP]; i--)
        stack->stackMemory[i-1] = stack->stackMemory[i];

    stack->GPR[SP]--;    

    return;
}

/* Unsure if these are needed
extern void allocateSpace(Stack* stack);
extern void deallocate(Stack* stack);
*/