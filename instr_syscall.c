#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instr_syscall.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"
#include "utilities.h"


void exitProgam(bin_instr_t i)
{
    exit(machine_types_sgnExt(i.syscall.offset));
}

void printString(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[SP]] = printf("%s", (char*) &stack->stackMemory->words[stack->GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)]);
}

void printChar(bin_instr_t i,  Stack* stack)
{
    stack->stackMemory->words[stack->GPR[SP]] = fputc(stack->stackMemory->words[stack->GPR[i.syscall.reg] + 
    machine_types_formOffset(i.syscall.offset)], stdout);
}


void readChar(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.syscall.reg] + machine_types_formOffset(i.syscall.offset)] = getc(stdin);
}

int startTrace(){
    return 1;
}

int stopTrace(){
    return 0;
}

void traceInstrPrint(bin_instr_t i, address_type* pc)
{
    fprintf(stdout, "%s%7d: %s\n", TRACE_INSTR_PREFIX, *pc, instruction_assembly_form(*pc, i));
}

void traceStatePrint(address_type* pc, uword_type* hi, uword_type* lo, Stack* stack)
{
    fprintf(stdout, "%8s: %-6d", PC_PRINT, *pc);

    if (*hi)
        fprintf(stdout, "%s: %-6d", HI_PRINT, *hi);
    
    if (*lo)
        fprintf(stdout, "%s: %-6d", LO_PRINT, *lo);
    
    newline(stdout);

    for(int c = 0; c <= RA; c++)
    {
        if (c == 5)
            newline(stdout);
        
        fprintf(stdout, "%s[%s]: %-6d", GPR_PRINT, regname_get(c), stack->GPR[c]);
    }
    newline(stdout);

    // current line length
    int len = 0;

    // if a zero is printed, dont print any zeros after that.
    int hasSkippedAhead = 0;
    int doubleZeros = 0;

    char* currentOut = (char*) malloc(sizeof(char)*MAX_DATA_LINE_LENGTH*2);

    for (int b = stack->GPR[GP]; b <= stack->GPR[FP]; b++) 
    {
        //ignore zero values not on the stack
        if(hasSkippedAhead && doubleZeros && stack->stackMemory->words[b] == 0 && b < stack->GPR[SP])
            continue;

        //line breaks and reset for stack memory
        if (len > MAX_DATA_LINE_LENGTH || b == stack->GPR[SP]){
            len = resetLen();
            
            if(b == stack->GPR[SP]){
                hasSkippedAhead = 0;
                doubleZeros = 0;
            }
        }
            
        
        // always print if its not a zero value
        if (stack->stackMemory->words[b] != 0)
        {
            doubleZeros = 0;
            hasSkippedAhead = 0;

            len += stdPrint(&currentOut, len, b, stack->stackMemory->words[b]);
        } 
        // first time we hit a 0
        else if (stack->stackMemory->words[b] == 0 && !hasSkippedAhead && !doubleZeros)
        {
            len += stdPrint(&currentOut, len, b, 0);
            doubleZeros =  1;
        }
        //initiate skipping and print ellipses
        else if (stack->stackMemory->words[b] == 0 && !hasSkippedAhead && doubleZeros)
        {
            sprintf(currentOut, "%s", DATA_SEPARATOR);
            len += strlen(currentOut);

            if(len > MAX_DATA_LINE_LENGTH)
                len = resetLen();

            printf("%8s", currentOut);
            hasSkippedAhead = 1;
        }
    }

    newline(stdout);
    newline(stdout);

    free(currentOut);
}

static int resetLen(){
    newline(stdout);
    return 0;
}

static int stdPrint(char** currentOut, int len, int adr, word_type instr){
    sprintf(*currentOut, "%8d: %-6d", adr, instr);
    printf("%s", *currentOut);

    if (len + strlen(*currentOut) > MAX_DATA_LINE_LENGTH)
         return resetLen();

    else return strlen(*currentOut);
}
