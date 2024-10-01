#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instr_syscall.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"
#include "utilities.h"

//TODO implement startTracing and stopTracing func

void exitProgam(bin_instr_t i)
{
    exit(machine_types_sgnExt(i.syscall.offset));
}

void printString(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[SP]] = printf("%s", stack->stackMemory->words[stack->GPR[i.syscall.reg] + 
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
    fprintf(stdout, "%s%7d:%8s\n", TRACE_INSTR_PREFIX, *pc, instruction_assembly_form(*pc, i));
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
    int printNextZero = 1;
    int hasSkippedAhead = 0;
    int doubleZeros = 0;

    char* currentOut = (char*) malloc(sizeof(char)*MAX_DATA_LINE_LENGTH*2);

    for (int b = stack->GPR[GP]; b <= stack->GPR[FP]; b++) 
    {
        if (len > MAX_DATA_LINE_LENGTH)
            len = resetLen(len);
        
        // always print if its not a zero value or on the stack
        if (stack->stackMemory->words[b] != 0)
        {
            printNextZero = 1;
            doubleZeros = 0;

            sprintf(currentOut, "%8d: %-6d", b, stack->stackMemory->words[b]);
            len += strlen(currentOut);
            printf("%s", currentOut);
        } else if(b >= stack->GPR[SP]){
            len = resetLen(len);
            
            sprintf(currentOut, "%8d: %-6d", b, stack->stackMemory->words[b]);
            len += strlen(currentOut);
            printf("%s", currentOut);
        }

        // this is the whole long thing that we do for the first time we hit a 0
        else if (stack->stackMemory->words[b] == 0 && !hasSkippedAhead && !doubleZeros)
        {
            sprintf(currentOut, "%8d: %-6d", b, 0);
            len += strlen(currentOut);
            printf("%s", currentOut);

            doubleZeros = 1;
        }

        else if (stack->stackMemory->words[b] == 0 && !hasSkippedAhead && doubleZeros)
        {

            sprintf(currentOut, "%8s", DATA_SEPARATOR);
            len += strlen(currentOut);
            printf("%s", currentOut);

            if (len > MAX_DATA_LINE_LENGTH)
            {
                newline(stdout);
                len = 0;
            }

            b = stack->GPR[SP] - 1;

            // we're supposed to print the sp-1 but only if its non-zero, otherwise skip it and newline
            if (stack->stackMemory->words[b] != 0)
            {
                sprintf(currentOut, "%8d: %-6d", b, stack->stackMemory->words[b]);
                len += strlen(currentOut);
                printf("%s", currentOut);
            }

            b++;

            newline(stdout);

            hasSkippedAhead = 1;
        }

        // (after skipping to sp) where the current value is zero, and a zero has not been printed directly before
        else if (stack->stackMemory->words[b] == 0 && hasSkippedAhead && printNextZero == 1)
        {
            sprintf(currentOut, "%8d: %-6d", b, 0);
            len += strlen(currentOut);
            printf("%s", currentOut);

            printNextZero = 0;
        }

        // (after skipping to sp) if current value is zero and previous value printed was 0, print a data separator instead
        else if (stack->stackMemory->words[b] == 0 && hasSkippedAhead && printNextZero == 0)
        {
            sprintf(currentOut, "%s", DATA_SEPARATOR);
            len += strlen(currentOut);
            printf("%s", currentOut);

            printNextZero = -1;
        }

        //if (b == stack->GPR[FP] && stack->stackMemory->words[b] == 0)
        //    fprintf(stdout, "%8d: %-6d", b, stack->stackMemory->words[b]);
    }

    newline(stdout);
    newline(stdout);

    free(currentOut);
}

static int resetLen(int len){
    newline(stdout);
    return len;
}
