#include "mips_instr.h"
#include "mips_internal.h"


mips_error BLTZ(mips_cpu_h state, uint8_t rs, uint16_t imm){
	if (!is_positive(state->GPReg[rs])){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error BGEZ(mips_cpu_h state, uint8_t rs, uint16_t imm){
	if (is_positive(state->GPReg[rs])){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error BLTZAL(mips_cpu_h state, uint8_t rs, uint16_t imm){
	state->GPReg[31] = state->pc + 8;
	if (!is_positive(state->GPReg[rs])){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error BGEZAL(mips_cpu_h state, uint8_t rs, uint16_t imm){
	state->GPReg[31] = state->pc + 8;
	if (is_positive(state->GPReg[rs])){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error BEQ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (state->GPReg[rs] == state->GPReg[rt]){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error BNE(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (state->GPReg[rs] != state->GPReg[rt]){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error BLEZ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (state->GPReg[rt] != 0){
		return mips_ExceptionInvalidInstruction;
	}
	//Equal to zero, or smaller than zero (bit32 == 1)
	if ((state->GPReg[rs] == 0) || !is_positive(state->GPReg[rs])){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error BGTZ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (state->GPReg[rt] != 0){
		return mips_ExceptionInvalidInstruction;
	}
	//Not Equal to zero, and smaller than zero (bit32 == 0)
	if (bigger_than(state->GPReg[rs], 0)){
		return state->advPC(sign_extend(imm));
	}
	else{
		return state->advPC(1);
	}
}

mips_error ADDI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t tmp = state->GPReg[rs] + sign_extend(imm);

	//Overflow ocurrs only if operands have same sign
	if (is_positive(state->GPReg[rs]) && is_positive(sign_extend(imm))){
		if (!is_positive(tmp)){
			return mips_ExceptionArithmeticOverflow;
		}
	}
	else if (!is_positive(state->GPReg[rs]) && !is_positive(sign_extend(imm))){
		if (is_positive(tmp)){
			return mips_ExceptionArithmeticOverflow;
		}
	}
	if (rt != 0){
		state->GPReg[rt] = tmp;
	}
	return state->advPC(1);
}

mips_error ADDIU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (rt != 0){
		state->GPReg[rt] = state->GPReg[rs] + sign_extend(imm);
	}
	return state->advPC(1);
}

mips_error SLTI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (rt != 0){
		state->GPReg[rt] = bigger_than(sign_extend(imm), state->GPReg[rs]);
	}
	return state->advPC(1);
}

mips_error SLTIU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (rt != 0){
		state->GPReg[rt] = sign_extend(imm) > state->GPReg[rs];
	}
	return state->advPC(1);
}

mips_error ANDI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t imm_extend = (0x00000000|imm);
	if (rt != 0){
		state->GPReg[rt] = state->GPReg[rs] & imm_extend;
	}
	return state->advPC(1);
}

mips_error ORI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t imm_extend = (0x00000000 | imm);
	if (rt != 0){
		state->GPReg[rt] = state->GPReg[rs] | imm_extend;
	}
	return state->advPC(1);
}

mips_error XORI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t imm_extend = (0x00000000 | imm);
	if (rt != 0){
		state->GPReg[rt] = state->GPReg[rs] ^ imm_extend;
	}
	return state->advPC(1);
}

mips_error LUI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	if (rs != 0){
		return mips_ExceptionInvalidInstruction;
	}
	else{
		if (rt != 0){
			uint32_t tmp = imm;
			state->GPReg[rt] = tmp << 16;
		}
		return state->advPC(1);
	}
}

mips_error LB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t address = state->GPReg[rs] + sign_extend(imm);
	uint32_t byte_adress = address & 0x3;
	address = address & 0xFFFFFFFC;
	uint8_t buffer[4];
	mips_error err = mips_mem_read(state->mem_handle, address, 4, buffer);

	if (err != mips_Success){
		return err;
	}

	uint32_t read = (to_big_Endi(buffer) >> (byte_adress * 8)) & 0xFF;
	state->GPReg[rt] = sign_extend8((uint8_t)read);

	return state->advPC(1);
}

mips_error LH(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t address = state->GPReg[rs] + sign_extend(imm);
	if ((address >> 31) > 0){
		return mips_ExceptionInvalidAlignment;
	}
	bool top_half = address >> 1 & 0x1;
	address = address & 0xFFFFFFFC;
	uint8_t buffer[4];
	mips_error err = mips_mem_read(state->mem_handle, address, 4, buffer);

	if (err != mips_Success){
		return err;
	}

	uint32_t read = (to_big_Endi(buffer) >> (top_half * 16)) & 0xFFFF;
	state->GPReg[rt] = sign_extend((uint16_t)read);

	return state->advPC(1);
}

mips_error LWL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LW(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t addr = state->GPReg[rs] + sign_extend(imm);

	uint8_t buffer[4];

	//Mem_read expected to handle alignment
	mips_error err = mips_mem_read(state->mem_handle, addr, 4, (uint8_t*) &buffer);

	if (err != mips_Success){
		return err;
	}
	else{
		if (rs != 0){
			state->GPReg[rs] = to_big_Endi((uint8_t*)&buffer);
		}
		return state->advPC(1);
	}
}

mips_error LBU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t address = state->GPReg[rs] + sign_extend(imm);
	uint32_t byte_adress = address & 0x3;
	address = address & 0xFFFFFFFC;
	uint8_t buffer[4];
	mips_error err = mips_mem_read(state->mem_handle, address, 4, buffer);

	if (err != mips_Success){
		return err;
	}

	state->GPReg[rt] = (to_big_Endi(buffer) >> (byte_adress * 8)) & 0xFF;

	return state->advPC(1);
}

mips_error LHU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t address = state->GPReg[rs] + sign_extend(imm);
	if ((address >> 31) > 0){
		return mips_ExceptionInvalidAlignment;
	}
	bool top_half = address >> 1 & 0x1;
	address = address & 0xFFFFFFFC;
	uint8_t buffer[4];
	mips_error err = mips_mem_read(state->mem_handle, address, 4, buffer);

	if (err != mips_Success){
		return err;
	}

	state->GPReg[rt] = (to_big_Endi(buffer) >> (top_half * 16)) & 0xFFFF;

	return state->advPC(1);
}

mips_error LWR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error SB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t address = state->GPReg[rs] + sign_extend(imm);
	uint32_t byte_adress = address & 0x3;
	address = address & 0xFFFFFFFC;
	uint32_t value = state->GPReg[rt] & (0xFF << (byte_adress * 8));
	mips_error err = mips_mem_read(state->mem_handle, address, 4, (uint8_t*)value);

	if (err != mips_Success){
		return err;
	}

	return state->advPC(1);
}

mips_error SH(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t address = state->GPReg[rs] + sign_extend(imm);
	if ((address >> 31) > 0){
		return mips_ExceptionInvalidAlignment;
	}
	bool top_half = address >> 1 & 0x1;
	address = address & 0xFFFFFFFC;
	uint32_t value = state->GPReg[rt] & (0xFFFF << (top_half * 16));
	mips_error err = mips_mem_read(state->mem_handle, address, 4, (uint8_t*)value);

	if (err != mips_Success){
		return err;
	}

	return state->advPC(1);
}

mips_error SW(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	uint32_t addr = state->GPReg[rs] + sign_extend(imm);

	//Mem_write expected to handle alignment
	mips_error err = mips_mem_write(state->mem_handle, addr, 4, (uint8_t*)state->GPReg[rt]);

	if (err != mips_Success){
		return err;
	}
	else{
		return state->advPC(1);
	}
}

mips_error J(mips_cpu_h state, uint32_t target){
	//Can not use advPC() because target is not an offset added to next pc
	state->pc = state->pcN;

	//NextPc = Top4Bits NextPC | target << 2)
	state->pcN = (state->pcN & 0xF0000000) | (target << 2) & 0x0FFFFFFF;

	if (state->debug_level >= 2){
		fprintf(state->debug_out, "New PC: 0x%08x     Next PC: 0x%08x \n-----------------------------\n", state->pc, state->pcN);
	}
	else if (state->debug_level == 1){
		fprintf(state->debug_out, "New PC: 0x%08x\n----------------------------\n", state->pc);
	}

	return mips_Success;
}

mips_error JAL(mips_cpu_h state, uint32_t target){
	//Link address is PC + 8 because must resume execution and delay slot (PC+4) has been executed
	state->GPReg[31] = state->pc + 8;

	//Jump 
	state->pcN = (state->pcN & 0xF0000000) | (target << 2) & 0xF0000000;
	return mips_Success;
}

mips_error SLL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rs != 0){
		return mips_ExceptionInvalidInstruction;
	}
	else if (rd != 0){
		state->GPReg[rd] = state->GPReg[rt] << sa;
	}
	return state->advPC(1);
}

mips_error SRL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rs != 0){
		return mips_ExceptionInvalidInstruction;
	}
	else if (rd != 0){
		state->GPReg[rd] = state->GPReg[rt] >> sa;
	}
	return state->advPC(1);
}

mips_error SRA(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rs != 0){
		return mips_ExceptionInvalidInstruction;
	}
	else if (rd != 0){
		if (!is_positive(state->GPReg[rt])){
			state->GPReg[rd] = state->GPReg[rt];
			for (int i = 0; i < sa; i++){
				state->GPReg[rd] = state->GPReg[rd] >> 1;
				state->GPReg[rd] = state->GPReg[rd] | 0x80000000;
			}
		}
		else{
			state->GPReg[rd] = state->GPReg[rt] >> sa;
		}
	}
	return state->advPC(1);
}

mips_error SLLV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	else if (rd != 0){
		uint32_t tmp = state->GPReg[rs] & 0x0000001F;
		state->GPReg[rd] = state->GPReg[rt] << tmp;
	}
	return state->advPC(1);
}

mips_error SRLV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	else if (rd != 0){
		uint32_t tmp = state->GPReg[rs] & 0x0000001F;
		state->GPReg[rd] = state->GPReg[rt] >> tmp;
	}
	return state->advPC(1);
}

mips_error SRAV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	else if (rd != 0){
		uint32_t shift = state->GPReg[rs] & 0x0000001F;
		if (!is_positive(state->GPReg[rt])){
			state->GPReg[rd] = state->GPReg[rt];
			for (unsigned i = 0; i < shift; i++){
				state->GPReg[rd] = state->GPReg[rd] >> 1;
				state->GPReg[rd] = state->GPReg[rd] | 0x80000000;
			}
		}
		else{
			state->GPReg[rd] = state->GPReg[rt] >> shift;
		}
	}
	return state->advPC(1);
}

mips_error JR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if ((rt != 0) || (sa!=0)){
		return mips_ExceptionInvalidInstruction;
	}

	if (rd != 0){
		state->GPReg[rd] = state->pc + 8;
	}

	state->pc = state->pcN;
	state->pcN = state->GPReg[rs];
	return mips_Success;

}

mips_error JALR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if ((rt != 0) || (rd != 0) || (sa != 0)){
		return mips_ExceptionInvalidInstruction;
	}

	state->pc = state->pcN;
	state->pcN = state->GPReg[rs];
	return mips_Success;;
}

mips_error MFHI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rs != 0 || rt != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	if (rd != 0){
		state->GPReg[rd] = state->HI;
	}
	return state->advPC(1);
}

mips_error MTHI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rd != 0 || rt != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	state-> HI = state->GPReg[rd];
	return state->advPC(1);
}

mips_error MFLO(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rs != 0 || rt != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	if (rd != 0){
		state->GPReg[rd] = state->LO;
	}
	return state->advPC(1);
}

mips_error MTLO(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rd != 0 || rt != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	state->HI = state->GPReg[rd];
	return state->advPC(1);
}

mips_error MULT(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rd != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	bool negative = false;
	if (!is_positive(state->GPReg[rs])){
		state->GPReg[rs] = twos_complement(state->GPReg[rs]);
		negative = true;
	}
	if (!is_positive(state->GPReg[rt])){
		state->GPReg[rt] = twos_complement(state->GPReg[rt]);
		negative = ~negative;
	}
	uint64_t tmp = state->GPReg[rs] * state->GPReg[rt];
	if (negative){
		tmp = twos_complement(tmp);
	}
	state->LO = tmp & 0xFFFFFFFF;
	state->HI = (tmp >> 32) & 0xFFFFFFFF;
	return state->advPC(1);
}

mips_error MULTU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rd != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	uint64_t tmp = state->GPReg[rs] * state->GPReg[rt];
	state->LO = tmp & 0xFFFFFFFF;
	state->HI = (tmp>>32) & 0xFFFFFFFF;
	return state->advPC(1);
}

mips_error DIV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rd != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}

	//Divide by 0 result is undefined
	if (state->GPReg[rt] == 0){
		return state->advPC(1);
	}

	bool negative = false;
	if (!is_positive(state->GPReg[rs])){
		state->GPReg[rs] = twos_complement(state->GPReg[rs]);
		negative = true;
	}
	if (!is_positive(state->GPReg[rt])){
		state->GPReg[rt] = twos_complement(state->GPReg[rt]);
		negative = ~negative;
	}

	uint64_t tmp = state->GPReg[rs] / state->GPReg[rt];
	if (negative){
		tmp = twos_complement(tmp);
	}
	state->LO = tmp & 0xFFFFFFFF;
	state->HI = (tmp >> 32) & 0xFFFFFFFF;
	return state->advPC(1);
}

mips_error DIVU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (rd != 0 || sa != 0){
		return mips_ExceptionInvalidInstruction;
	}

	//Divide by 0 result is undefined
	if (state->GPReg[rt]==0){
		return state->advPC(1);
	}

	uint64_t tmp = state->GPReg[rs] / state->GPReg[rt];
	state->LO = tmp & 0xFFFFFFFF;
	state->HI = (tmp >> 32) & 0xFFFFFFFF;
	return state->advPC(1);
}

mips_error ADD(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	uint32_t tmp = state->GPReg[rs] + state->GPReg[rt];

	//Overflow ocurrs only if operands have same sign
	if (is_positive(state->GPReg[rs]) && is_positive(state->GPReg[rt])){
		if (!is_positive(tmp)){
			return mips_ExceptionArithmeticOverflow;
		}
	}
	else if (!is_positive(state->GPReg[rs]) && !is_positive(state->GPReg[rt])){
		if (is_positive(tmp)){
			return mips_ExceptionArithmeticOverflow;
		}
	}

	if (rd != 0){
		state->GPReg[rd] = tmp;
	}
	return state->advPC(1);
}

mips_error ADDU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	if (rd != 0){
		state->GPReg[rd] = state->GPReg[rt] + state->GPReg[rs];
	}
	return state->advPC(1);
}

mips_error SUB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	uint32_t tmp = state->GPReg[rs] - state->GPReg[rt];

	//Overflow ocurrs only if operands have same sign (after negative applied to second operand)
	if (is_positive(state->GPReg[rs]) && !is_positive(state->GPReg[rt])){
		if (!is_positive(tmp)){
			return mips_ExceptionArithmeticOverflow;
		}
	}
	else if (!is_positive(state->GPReg[rs]) && is_positive(state->GPReg[rt])){
		if (is_positive(tmp)){
			return mips_ExceptionArithmeticOverflow;
		}
	}
	if (rd != 0){
		state->GPReg[rd] = tmp;
	}
	return state->advPC(1);
}

mips_error SUBU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	if (rd != 0){
		state->GPReg[rd] = state->GPReg[rs] - state->GPReg[rt];
	}
	return state ->advPC(1);
}

mips_error AND(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}

	if (rd != 0){
		state->GPReg[rd] = state->GPReg[rs] & state->GPReg[rt];
	}
	return state->advPC(1);
}

mips_error OR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}

	if (rd != 0){
		state->GPReg[rd] = state->GPReg[rs] | state->GPReg[rt];
	}
	return state->advPC(1);
}

mips_error XOR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}

	if (rd != 0){
		state->GPReg[rd] = state->GPReg[rs] ^ state->GPReg[rt];
	}
	return state->advPC(1);
}

mips_error SLT(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	if (rd != 0){
		state->GPReg[rd] = bigger_than(state->GPReg[rt], state->GPReg[rs]);
	}
	return state->advPC(1);
}

mips_error SLTU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa){
	if (sa != 0){
		return mips_ExceptionInvalidInstruction;
	}
	if (rd != 0){
		state->GPReg[rd] = state->GPReg[rs] < state->GPReg[rt];
	}
	return state->advPC(1);
}

uint32_t sign_extend(uint16_t in){
	uint32_t tmp = in;
	if ((in >> 15) == 1){
		return(tmp | 0xFFFF0000);
	}
	else{
		return tmp;
	}
}

uint32_t sign_extend8(uint8_t in){
	uint32_t tmp = in;
	if ((in >> 7) == 1){
		return(tmp | 0xFFFFFF00);
	}
	else{
		return tmp;
	}
}

bool is_positive(uint32_t in){
	return (in >> 31) == 0;
}

bool bigger_than(uint32_t a, uint32_t b){
	//Both positive/negative , unsigned compare
	if (is_positive(a) && is_positive(b) ||
		!is_positive(a) && !is_positive(b)
		){
		return a > b;
	}
	//Alternate signs -> unsigned compare is wrong -> opposite
	else {
		return a < b;
	}
}

uint64_t twos_complement(uint64_t a){
	return (~a) + 1;
}