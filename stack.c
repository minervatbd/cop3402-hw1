#include "machine_types.h"
#include "stack.h"

Stack* initalizeStack(){
    Stack* myStack = (Stack*) malloc(sizeof(Stack));
    myStack->fp = 0;
    myStack->sp = 1;
    myStack->topOffset = 0;
    return myStack;
}

uword_type ARSize(Stack* stack){
    return stack->sp - stack->fp; 
}
//unsure of how to implement this for now (is this size of AR + size of stack memory? or just stack memory?)
uword_type stackSize(Stack* stack){
    
}
 
address_type ARTop(Stack* stack){
    return stack->sp;
}
 
address_type ARBottom(Stack* stack){
    return stack->fp;
}

//if sp > fp and !sp> max size, 1 for invariant pass, 2 to indicate stack is full
int stackOkay(Stack* stack){
    if(stack->sp <= stack->fp)
        return 0;
    if(stack->sp > STACK_HEIGHT)
        return 0;
    else if(stack->sp == STACK_HEIGHT)
        return 2;
    return 1;
}

void push(Stack* stack, word_type val){
    stack->stackMemory[stack->sp + stack->topOffset] = val;
    stack->topOffset++;

    return;
}

void pop(Stack* stack){
    stack->stackMemory[stack->sp + stack->topOffset] = 0;
    stack->topOffset--;

    return;
}

word_type peek(Stack* stack){
    return stack->stackMemory[stack->sp + stack->topOffset];
}


void addAR(Stack* stack, word_type AR){
    stack->stackMemory[stack->sp-1] = AR;
    for(int i= stack->sp + stack->topOffset; i > stack->sp; i--)
        stack->stackMemory[i+1] = stack->stackMemory[i];
    
    stack->sp++;

    return;
}

void subAR(Stack* stack){
    stack->stackMemory[stack->sp-1] = 0;
    for(int i= stack->sp + stack->topOffset; i > stack->sp; i--)
        stack->stackMemory[i-1] = stack->stackMemory[i];

    stack->sp--;    

    return;
}

/* Unsure if these are needed
extern void allocateSpace(Stack* stack);
extern void deallocate(Stack* stack);
*/