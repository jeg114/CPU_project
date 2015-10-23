/*Computer architecture 2 - 2015 - Coursework 1
		By: Jesús Erlantz García Condado
		Username: jeg114
		Date:17/10/2015
*/

#include "mips_core.h"
#include "mips.h"
#include "mips_instr.h"
#include "mips_internal.h"



using namespace std;

mips_cpu_h mips_cpu_create(mips_mem_h mem){
	mips_cpu_h new_cpu = new mips_cpu_impl (mem);
	return new_cpu;
}

mips_error mips_cpu_reset(mips_cpu_h state){
	state->pc = 0;
	state->LO = 0;
	state->HI = 0;
	for (int i = 0; i <= 31; i++){
		state -> GPReg[i] = 0;
	}
	//Can be unsuccesful??
	return mips_Success;
}

mips_error mips_cpu_get_register(mips_cpu_h state, unsigned index, uint32_t *value){
	if (index > 31){
		return mips_ErrorInvalidArgument;
	}
	else{
		*value = state->GPReg[index];
		return mips_Success;
	}
}

mips_error mips_cpu_set_register(mips_cpu_h state, unsigned index, uint32_t value){
	if (index > 31){
		return mips_ErrorInvalidArgument;
	}
	else{
		state->GPReg[index] = value;
		return mips_Success;
	}
}

mips_error mips_cpu_set_pc(mips_cpu_h state, uint32_t pc){
	if (pc % 4 != 0){
		return mips_ExceptionInvalidAlignment;
	}
	else{
		state->pc = pc;
		state->pcN = pc + 4;
		return mips_Success;
	}
}

mips_error mips_cpu_get_pc(mips_cpu_h state, uint32_t *pc){
	*pc = state->pc;
	return mips_Success;
}

void mips_cpu_free(mips_cpu_h state){
	if (state != NULL){
		delete state;
	}
}

uint32_t to_big_Endi(const uint8_t *pData)
{
	return
		(((uint32_t)pData[0]) << 24)
		|
		(((uint32_t)pData[1]) << 16)
		|
		(((uint32_t)pData[2]) << 8)
		|
		(((uint32_t)pData[3]) << 0);
}

void to_small_Endi(const uint32_t Data, uint8_t* output){
	output[0] = (Data >> 24) & 0xFF;
	output[1] = (Data >> 16) & 0xFF;
	output[2] = (Data >> 8) & 0xFF;
	output[3] = (Data >> 0) & 0xFF;
}

mips_error mips_cpu_step(mips_cpu_h state){
	//Debug information
	if (state->debug_level >= 1){ fprintf(state->debug_out, "\n----------- NEW STEP -------- \nPC: 0x%08x \n", state->pc); }
	if (state->debug_level >= 4){
		fprintf(state->debug_out, "Registers: \n");
		for (int i = 0; i <= 31; i++){
			fprintf(state->debug_out, "$%i: 0x%08x \n", i, state->GPReg[i]);
		}
		fprintf(state->debug_out, "LO: 0x%08x \nHI: 0x%08x\n", state->LO, state->HI);
	}

	//Fetch Instruction
	uint8_t buffer[4];
	mips_error step_err = mips_mem_read(state->mem_handle, state->pc, 4,  buffer);

	if (state->debug_level >= 5){ fprintf(state->debug_out, "Err MemReadInstr: %4d\n", step_err); }

	uint32_t instr = to_big_Endi(buffer);

	if (state->debug_level >= 2){ fprintf(state->debug_out, "Instr: %#010x\n", instr); }

	if (step_err != mips_Success){
		return step_err;
	}
	else{
		//Decode Instruction
		uint8_t opcode = instr >> 26;
		if (opcode == 0){
			//R - Type Instr
			/*
			--- Opcode --- rs --- rt --- rd --- sa --- function ---
			--- 6 Bits ---  5 ---  5 ---  5 ---  5 ---    6     ---
			*/

			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: R\n", instr); }

			uint8_t rs = (instr >> 21) & 0x1f;
			uint8_t rt = (instr >> 16) & 0x1f;
			uint8_t rd = (instr >> 11) & 0x1f;
			uint8_t sa = (instr >> 6) & 0x1f;
			uint8_t function = instr & 0x3f;

			if (state->debug_level >= 3){ fprintf(state->debug_out, "Op: 0x%2x    rs: %i   rt: %i   rd: %i   sa: %i   func: 0x%2x  \n", opcode, rs, rt, rd, sa, function); }

			//Execute Appropriate function
			switch (function){
			case 0:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SLL\n");
				}
				step_err = SLL(state, rs, rt, rd, sa);
				break;
			case 2:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SRL\n");
				}
				step_err = SRL(state, rs, rt, rd, sa);
				break;
			case 3:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SRA\n");
				}
				step_err = SRA(state, rs, rt, rd, sa);
				break;
			case 4:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SLLV\n");
				}
				step_err = SLLV(state, rs, rt, rd, sa);
				break;
			case 6:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SRLV\n");
				}
				step_err = SRLV(state, rs, rt, rd, sa);
				break;
			case 7:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SRAV\n");
				}
				step_err = SRAV(state, rs, rt, rd, sa);
				break;
			case 8:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "JR\n");
				}
				step_err = JR(state, rs, rt, rd, sa);
				break;
			case 9:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "JALR\n");
				}
				step_err = JALR(state, rs, rt, rd, sa);
				break;
			case 16:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "MFHI\n");
				}
				step_err = MFHI(state, rs, rt, rd, sa);
				break;
			case 17:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "MTHI\n");
				}
				step_err = MTHI(state, rs, rt, rd, sa);
				break;
			case 18:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "MFLO\n");
				}
				step_err = MFLO(state, rs, rt, rd, sa);
				break;
			case 19:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "MTLO\n");
				}
				step_err = MTLO(state, rs, rt, rd, sa);
				break;
			case 24:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "MULT\n");
				}
				step_err = MULT(state, rs, rt, rd, sa);
				break;
			case 25:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "MULTU\n");
				}
				step_err = MULTU(state, rs, rt, rd, sa);
				break;
			case 26:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "DIV\n");
				}
				step_err = DIV(state, rs, rt, rd, sa);
				break;
			case 27:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "DIVU\n");
				}
				step_err = DIVU(state, rs, rt, rd, sa);
				break;
			case 32:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "ADD\n");
				}
				step_err = ADD(state, rs, rt, rd, sa);
				break;
			case 33:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "ADDU\n");
				}
				step_err = ADDU(state, rs, rt, rd, sa);
				break;
			case 34:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SUB\n");
				}
				step_err = SUB(state, rs, rt, rd, sa);
				break;
			case 35:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SUBU\n");
				}
				step_err = SUBU(state, rs, rt, rd, sa);
				break;
			case 36:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "AND\n");
				}
				step_err = AND(state, rs, rt, rd, sa);
				break;
			case 37:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "OR\n");
				}
				step_err = OR(state, rs, rt, rd, sa);
				break;
			case 38:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "XOR\n");
				}
				step_err = XOR(state, rs, rt, rd, sa);
				break;
			case 42:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SLT\n");
				}
				step_err = SLT(state, rs, rt, rd, sa);
				break;
			case 43:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SLTU\n");
				}
				step_err = SLTU(state, rs, rt, rd, sa);
				break;
			default: return mips_ExceptionInvalidInstruction;
			}
		}
		else if (opcode >> 1 == 1){
			//J - Type Instr
			/*
			--- Opcode --- target ---
			--- 6 Bits ---   26   ---
			*/

			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: J\n", instr); }

			uint32_t target = instr & 0x3ffffff;

			switch (opcode){
			case 2: 
				if (state->debug_level > 0){ 
					fprintf(state->debug_out, "J\n"); 
				}
				step_err =  J(state, target);
				break;
			case 3: 
				if (state->debug_level > 0){ 
					fprintf(state->debug_out, "JAL\n"); 
				}
				step_err = JAL(state, target);
				break;
			default: step_err =  mips_ExceptionInvalidInstruction;
			}

		}
		else if(opcode >> 2 != 2){	//Opcode 0010XX reserved for coprocessor instructions
			//I - Type Instr
			/*
			--- Opcode --- rs --- rt --- immediate ---
			--- 6 Bits ---  5 ---  5 ---     16    ---
			*/
			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: I\n", instr); }
			uint8_t rs = (instr >> 21) & 0x1f;
			uint8_t rt = (instr >> 16) & 0x1f;
			uint16_t imm = instr & 0xffff;

			switch (opcode){
			case 1:
				switch (rt){
				case 0:
					if (state->debug_level > 0){ 
						fprintf(state->debug_out, "BLTZ\n"); 
					}
					step_err = BLTZ(state, rs, imm);
					break;
				case 1: 
					if (state->debug_level > 0){ fprintf(state->debug_out, "BGEZ\n"); 
					}
					step_err = BGEZ(state, rs, imm);
					break;
				case 16:
					if (state->debug_level > 0){ 
						fprintf(state->debug_out, "BLTZAL\n"); 
					}
					step_err = BLTZAL(state, rs, imm);
					break;
				case 17: 
					if (state->debug_level > 0){ 
						fprintf(state->debug_out, "BEGEZAL\n");
					}
					step_err = BGEZAL(state, rs, imm);
					break;
				default:
					step_err = mips_ExceptionInvalidInstruction;
				}
			case 4:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "BEQ\n");
				}
				step_err = BEQ(state, rs, rt, imm);
				break;
			case 5:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "BNE\n");
				}
				step_err = BNE(state, rs, rt, imm);
				break;
			case 6:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "BLEZ\n");
				}
				step_err = BLEZ(state, rs, rt, imm);
				break;
			case 7:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "BGTZ\n");
				}
				step_err = BGTZ(state, rs, rt, imm);
				break;
			case 8:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "ADDI\n");
				}
				step_err = ADDI(state, rs, rt, imm);
				break;
			case 9:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "ADDIU\n");
				}
				step_err = ADDIU(state, rs, rt, imm);
				break;
			case 10:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SLTI\n");
				}
				step_err = SLTI(state, rs, rt, imm);
				break;
			case 11:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SLTIU\n");
				}
				step_err = SLTIU(state, rs, rt, imm);
				break;
			case 12:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "ANDI\n");
				}
				step_err = ANDI(state, rs, rt, imm);
				break;
			case 13:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "ORI\n");
				}
				step_err = ORI(state, rs, rt, imm);
				break;
			case 14:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "XORI\n");
				}
				step_err = XORI(state, rs, rt, imm);
				break;
			case 15:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LUI\n");
				}
				step_err = LUI(state, rs, rt, imm);
				break;
			case 32:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LB\n");
				}
				step_err = LB(state, rs, rt, imm);
				break;
			case 33:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LH\n");
				}
				step_err = LH(state, rs, rt, imm);
				break;
			case 34:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LWL\n");
				}
				step_err = LWL(state, rs, rt, imm);
				break;
			case 35:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LW\n");
				}
				step_err = LW(state, rs, rt, imm);
				break;
			case 36:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LBU\n");
				}
				step_err = LBU(state, rs, rt, imm);
				break;
			case 37:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LHU\n");
				}
				step_err = LHU(state, rs, rt, imm);
				break;
			case 38:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "LWR\n");
				}
				step_err = LWR(state, rs, rt, imm);
				break;
			case 40:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SB\n");
				}
				step_err = SB(state, rs, rt, imm);
				break;
			case 41:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SH\n");
				}
				step_err = SH(state, rs, rt, imm);
				break;
			case 43:
				if (state->debug_level > 0){
					fprintf(state->debug_out, "SW\n");
				}
				step_err = SW(state, rs, rt, imm);
				break;

			default: step_err = mips_ExceptionInvalidInstruction;
			}
		}
		else{
			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: NONE (eg Coprocessor instructions opcode)\n"); }
			step_err =  mips_ExceptionInvalidInstruction;
		}
	}
	if (state->debug_level >= 5){ fprintf(state->debug_out, "StepError 0x%08x\n", step_err); }
	return step_err;
}

mips_error mips_cpu_set_debug_level(mips_cpu_h state, unsigned level, FILE *dest){
	if (level == 0){
		state->debug_level = 0;
		return mips_Success;
	}
	else if(dest != NULL){
		state->debug_out = dest;
		state->debug_level = level;
		return mips_Success;
	}
	else{
		return mips_ErrorInvalidArgument;
	}
}

mips_error mips_cpu_impl::advPC(uint32_t offset){
	pc = pcN;
	pcN = pcN + (offset << 2);
	if (debug_level >= 2){
		fprintf(debug_out, "New PC: 0x%08x     Next PC: 0x%08x \n-----------------------------\n", pc, pcN);
	}
	else if (debug_level == 1){
		fprintf(debug_out, "New PC: 0x%08x\n----------------------------\n", pc);
	}
	return mips_Success;
}


