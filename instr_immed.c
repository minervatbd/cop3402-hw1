#include "instr_immed.h"
#include "machine.h"
#include "machine_types.h"
#include "regname.h"
#include "stack.h"

// TEMP VARS TODO
union mem_u tempMem3;

void addImmed(bin_instr_t i, Stack* stack)
{
	tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] + machine_types_sgnExt(i.immed.immed);
}

void andImmed(bin_instr_t i, Stack* stack)
{
	tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] & machine_types_zeroExt(i.immed.immed);
}

void borImmed(bin_instr_t i, Stack* stack)
{
	tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] | machine_types_zeroExt(i.immed.immed);
}

void norImmed(bin_instr_t i, Stack* stack)
{
	tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	!(tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] | machine_types_zeroExt(i.immed.immed));
}

void xorImmed(bin_instr_t i, Stack* stack)
{
	tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] =  
	tempMem3.uwords[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] ^ machine_types_zeroExt(i.immed.immed);
}

void branchOnEqual(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(tempMem3.words[stack->GPR[SP]] = tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)]) {
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchGreaterEqualThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] >= 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchGreaterThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] > 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchLessEqualThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] <= 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchLessThanZero(bin_instr_t i, Stack* stack, address_type* pc)
{
	if(tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)] < 0){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}

void branchNotEqual(bin_instr_t i, Stack* stack, address_type* pc)
{   
	if(tempMem3.words[stack->GPR[SP]] != tempMem3.words[stack->GPR[i.immed.reg] + machine_types_formOffset(i.immed.offset)]){
    	*pc = (*pc -1) + machine_types_formOffset(i.immed.immed);
	}
}
