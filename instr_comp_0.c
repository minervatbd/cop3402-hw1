#include "instr_comp_0.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

void add(bin_instr_t i, Stack* stack)
{
    /*memory[GPR[t] + formOffset(ot)] ← memory[GPR[$sp]] + (memory[GPR[s] + formOffset(os)])*/
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = stack->stackMemory->words[stack->GPR[SP]] + 
    (stack->stackMemory->words[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)]);
   
}

void subtract(bin_instr_t i, Stack* stack)
{
    //memory[GPR[t] + formOffset(ot)] ← memory[GPR[$sp]] − (memory[GPR[s] + formOffset(os)])
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = stack->stackMemory->words[stack->GPR[SP]] - 
    (stack->stackMemory->words[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)]);
}

void copyWord(bin_instr_t i, Stack* stack)
{
    //memory[GPR[t] + formOffset(ot)] ← memory[GPR[s] + formOffset(os)]
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = 
    stack->stackMemory->words[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)];

}

void bitwiseAnd(bin_instr_t i, Stack* stack)
{
    //umemory[GPR[t] + formOffset(ot)]; ← umemory[GPR[$sp]] ∧ (umemory[GPR[s] + formOffset(os)]);
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = stack->stackMemory->uwords[stack->GPR[SP]] &
    (stack->stackMemory->uwords[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)]);
}

void bitwiseOr(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = stack->stackMemory->uwords[stack->GPR[SP]] |
    (stack->stackMemory->uwords[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)]);
}

void bitwiseNor(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = !(stack->stackMemory->uwords[stack->GPR[SP]] |
    (stack->stackMemory->uwords[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)]));
}

void bitwiseXor(bin_instr_t i, Stack* stack)
{
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = stack->stackMemory->uwords[stack->GPR[SP]] ^
    (stack->stackMemory->uwords[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)]);
}

void loadWord(bin_instr_t i, Stack* stack)
{
    //GPR[t] ← memory[GPR[s] + formOffset(os)]
    stack->GPR[i.comp.rt] = stack->stackMemory->words[stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os)];
}

void storeWord(bin_instr_t i, Stack* stack)
{
    //memory[GPR[t] + formOffset(ot)] ← GPR[s]
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = stack->GPR[i.comp.rs];

}

void storeAddr(bin_instr_t i, Stack* stack)
{
    //memory[GPR[t] + formOffset(ot)] ← (GPR[s] + formOffset(os))
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = (stack->GPR[i.comp.rs] + machine_types_formOffset(i.comp.os));

}

void loadWordIndirect(bin_instr_t i, Stack* stack)
{
    //memory[GPR[t] + formOffset(ot)] ← memory[memory[GPR[s] + formOffset(os)]]
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = stack->stackMemory->words[stack->stackMemory->words[stack->GPR[i.comp.rs] 
    + machine_types_formOffset(i.comp.os)]];
}

void negate(bin_instr_t i, Stack* stack)
{
    //memory[GPR[t] + formOffset(ot)] ← −memory[GPR[s] + formOffset(os)]
    stack->stackMemory->words[stack->GPR[i.comp.rt] + machine_types_formOffset(i.comp.ot)] = -stack->stackMemory->words[stack->GPR[i.comp.rs] 
    + machine_types_formOffset(i.comp.os)];
}
