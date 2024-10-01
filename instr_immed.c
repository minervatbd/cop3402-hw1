#include "instr_immed.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

void addImmed(bin_instr_t i, Stack* stack)
{
	//debug temp
	printf("register: %u\n", i.immed.reg);
	stack->stackMemory->words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] = 
	stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] + machine_types_sgnExt(i.immed.immed);
	printf("made it here\n");
}

void andImmed(bin_instr_t i, Stack* stack)
{
	stack->stackMemory->words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] & machine_types_zeroExt(i.immed.immed);
}

void borImmed(bin_instr_t i, Stack* stack)
{
	stack->stackMemory->words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] | machine_types_zeroExt(i.immed.immed);
}

void norImmed(bin_instr_t i, Stack* stack)
{
	stack->stackMemory->words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	!(stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] | machine_types_zeroExt(i.immed.immed));
}

void xorImmed(bin_instr_t i, Stack* stack)
{
	stack->stackMemory->words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] ^ machine_types_zeroExt(i.immed.immed);
}

void branchOnEqual(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(stack->stackMemory->uwords[stack->GPR[SP]] == stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)]) {
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchGreaterEqualThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] >= 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchGreaterThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] > 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchLessEqualThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] <= 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchLessThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] < 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchNotEqual(bin_instr_t i, Stack* stack, address_type* pc)
{   
	if(stack->stackMemory->uwords[stack->GPR[SP]] != stack->stackMemory->uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)]){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}
