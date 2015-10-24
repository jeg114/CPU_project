#ifndef mips_internal
#define mips_internal

#include "mips.h"

struct mips_cpu_impl{
	//Program Counter
	uint32_t pc;
	uint32_t pcN;

	//General Purpose Registers
	uint32_t GPReg[32];

	//Special registers for MUL / DIV instructions
	uint32_t LO;
	uint32_t HI;

	mips_mem_h mem_handle;

	/*
	Debug Levels

	0 - NOTHING PRINTED
	1 - Initial PC, Instruction (String), New PC
	2 - Initial PC, Instruction (32 Bit), type, Instruction (String), New PC, Next PC
	3 - Initial PC, Instruction (32 Bit), type, Instruction (String), Decoded values (rt, rd, imm...), Next PC
	4 - Same as 3 + initial state of cpu
	5 - Same as 4 + Errors at all stages (eg Err Memread: 0)
	*/
	unsigned debug_level;
	FILE* debug_out;

	mips_cpu_impl(mips_mem_h mem) : 
		mem_handle(mem), 
		pc(0), 
		pcN(4), 
		LO(0), 
		HI(0), 
		debug_level(0), 
		debug_out(NULL){
		for (int i = 0; i <= 31; i++){
			GPReg[i] = 0;
		}
	}

	mips_error advPC(uint32_t offset);
};

uint32_t to_big_Endi(const uint8_t *pData);

void to_small_Endi(const uint32_t Data, uint8_t* output);

#endif