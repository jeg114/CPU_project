/*Computer architecture 2 - 2015 - Coursework 1
By: Jesús Erlantz García Condado
Username: jeg114
Date:17/10/2015
*/
#define _CRT_SECURE_NO_DEPRECATE
#include "mips.h"
#include <string> 
#include <iostream> 


using namespace std;

/*
32 bit instr from a string function code (ADD, SUB, JR..) an R-type instruction,
if that function is not included, behaviour undefined

*/
uint32_t R_type_instr(uint32_t rs, uint32_t rt, uint32_t rd, uint32_t sa, uint32_t function);

/*
32 bit instr from a string function code (ADDI, SUBI, ..) an I-type instruction,
if that function is not included, behaviour undefined

*/
uint32_t I_type_instr(std::string instr, uint32_t rs, uint32_t rt, uint32_t imm);

/*
32 bit instr from a string function code (ADDI, SUBI, ..) an J-type instruction,
if that function is not included, behaviour undefined

*/
uint32_t J_type_instr(std::string instr, uint32_t target);

void to_small_Endi(const uint32_t Data, uint8_t* output);

uint32_t sign_extend18(uint32_t in);

void test_mips_ADD(mips_cpu_h state, mips_mem_h mem);
void test_mips_ADDU(mips_cpu_h state, mips_mem_h mem);
void test_mips_SUBU(mips_cpu_h state, mips_mem_h mem);
void test_mips_SUB(mips_cpu_h state, mips_mem_h mem);
void test_mips_AND(mips_cpu_h state, mips_mem_h mem);
void test_mips_OR(mips_cpu_h state, mips_mem_h mem);
void test_mips_XOR(mips_cpu_h state, mips_mem_h mem);
void test_mips_ADDI(mips_cpu_h state, mips_mem_h mem);
void test_mips_ADDIU(mips_cpu_h state, mips_mem_h mem);
void test_mips_ANDI(mips_cpu_h state, mips_mem_h mem);
void test_mips_ORI(mips_cpu_h state, mips_mem_h mem);
void test_mips_XORI(mips_cpu_h state, mips_mem_h mem);
void test_mips_SLTU(mips_cpu_h state, mips_mem_h mem);
void test_mips_SLT(mips_cpu_h state, mips_mem_h mem);
void test_mips_SLTI(mips_cpu_h state, mips_mem_h mem);
void test_mips_SLTIU(mips_cpu_h state, mips_mem_h mem);
void test_mips_SLL(mips_cpu_h state, mips_mem_h mem);
void test_mips_SRL(mips_cpu_h state, mips_mem_h mem);
void test_mips_SRLV(mips_cpu_h state, mips_mem_h mem);
void test_mips_SLLV(mips_cpu_h state, mips_mem_h mem);
void test_mips_SRAV(mips_cpu_h state, mips_mem_h mem);
void test_mips_SRA(mips_cpu_h state, mips_mem_h mem);
void test_mips_LUI(mips_cpu_h state, mips_mem_h mem);
void test_mips_MFHI(mips_cpu_h state, mips_mem_h mem);
void test_mips_MTHI(mips_cpu_h state, mips_mem_h mem);
void test_mips_MFLO(mips_cpu_h state, mips_mem_h mem);
void test_mips_MTLO(mips_cpu_h state, mips_mem_h mem);
void test_mips_J(mips_cpu_h state, mips_mem_h mem);
void test_mips_BLTZ(mips_cpu_h state, mips_mem_h mem);
void test_mips_BLTZAL(mips_cpu_h state, mips_mem_h mem);
void test_mips_BLEZ(mips_cpu_h state, mips_mem_h mem);
void test_mips_BGEZAL(mips_cpu_h state, mips_mem_h mem);
void test_mips_BGEZ(mips_cpu_h state, mips_mem_h mem);
void test_mips_BEQ(mips_cpu_h state, mips_mem_h mem);
void test_mips_BNE(mips_cpu_h state, mips_mem_h mem);
void test_mips_BGTZ(mips_cpu_h state, mips_mem_h mem);
void test_mips_MF_MT_HI_LO(mips_cpu_h state, mips_mem_h mem);
void test_mips_MULTU(mips_cpu_h state, mips_mem_h mem);

mips_error set_step_read(mips_cpu_h state,
	const uint32_t& reg1,
	const uint32_t& reg1_v,
	const uint32_t& reg2,
	const uint32_t& reg2_v,
	const uint32_t& instr,
	const uint32_t& regRead,
	uint32_t& regRead_v,
	mips_mem_h mem);

int main(){

	mips_mem_h mem = mips_mem_create_ram(1024, 4);
	mips_cpu_h cpu = mips_cpu_create(mem);

	int debug;
	FILE* file_h = NULL;
	//cout << "Set Debug level: " << endl;
	//cin >> debug;
	//if (debug > 0){
	//	string filename;
	//	cout << "Input file name for output / stderr / stdout, (if file not found it will be created)" << endl;
	//	cin >> filename;
	//	if (filename == "stderr"){
	//		file_h = stderr;
	//	}
	//	else if (filename == "stdout"){
	//		file_h = stdout;
	//	}
	//	else{
	//		file_h = fopen(filename.c_str(), "w");
	//	}
	//}

	debug = 3;
	file_h = stdout;

	mips_cpu_set_debug_level(cpu, debug, file_h);

	mips_test_begin_suite();
	//test_mips_SLTU(cpu, mem);
	//test_mips_SLT(cpu, mem);
	//test_mips_SLTI(cpu, mem);
	//test_mips_SLTIU(cpu, mem);
	//test_mips_LUI(cpu, mem);
	//test_mips_SLL(cpu, mem);
	//test_mips_SRL(cpu, mem);
	//test_mips_SRLV(cpu, mem);
	//test_mips_SLLV(cpu, mem);
	//test_mips_SRAV(cpu, mem);
	//test_mips_SRA(cpu, mem);
	//test_mips_ADD(cpu, mem);
	//test_mips_ADDI(cpu, mem);
	//test_mips_ADDIU(cpu, mem);
	//test_mips_ANDI(cpu, mem);
	//test_mips_ORI(cpu, mem);
	//test_mips_XORI(cpu, mem);
	//test_mips_SUB(cpu, mem);
	//test_mips_ADDU(cpu, mem);
	//test_mips_SUBU(cpu, mem);
	//test_mips_AND(cpu,mem);
	//test_mips_OR(cpu, mem);
	//test_mips_XOR(cpu, mem);
	//test_mips_J(cpu,mem);
	//test_mips_BLTZ(cpu, mem);
	//test_mips_BLEZ(cpu, mem);
	//test_mips_BEQ(cpu, mem);
	//test_mips_BNE(cpu, mem);
	test_mips_MF_MT_HI_LO(cpu, mem);
	test_mips_MULTU(cpu, mem);
	//test_mips_BGTZ(cpu, mem);
	//test_mips_BGEZ(cpu, mem);
	//test_mips_BLTZAL(cpu, mem);
	//test_mips_BGEZAL(cpu, mem);
	mips_test_end_suite();

	cin.get();

	return 0;
}

uint32_t R_type_instr(uint32_t rs, uint32_t rt, uint32_t rd, uint32_t sa, uint32_t function){

	uint32_t instr_code =
		(0ul << 26) // opcode = 0
		|
		(rs << 21) // srca = r4
		|
		(rt << 16) // srcb = r5
		|
		(rd << 11) // dst = r3
		|
		(sa << 6) // shift = 0
		|
		(function << 0);

	return instr_code;
}

uint32_t I_type_instr(uint32_t opcode, uint32_t rs, uint32_t rt, uint32_t imm){
	uint32_t instr_code =
		(opcode << 26) // opcode = 0
		|
		(rs << 21) // srca = r4
		|
		(rt << 16) // srcb = r5
		|
		(imm & 0x0000FFFF);

	return instr_code;
}

uint32_t J_type_instr(bool is_J, uint32_t target){

	uint32_t opcode;

	if (is_J){
		opcode = 0x2;
	}
	else {
		opcode = 0x3;
	}

	uint32_t instr_code =
		(opcode << 26)
		|
		(target << 0);

	return instr_code;
}

mips_error set_step_read(mips_cpu_h state, 
	const uint32_t& reg1, 
	const uint32_t& reg1_v, 
	const uint32_t& reg2, 
	const uint32_t& reg2_v, 
	const uint32_t& instr, 
	const uint32_t& regRead, 
	uint32_t& regRead_v,
	mips_mem_h mem){

	mips_error err = mips_Success;

	if (reg1 <= 31){
		err = mips_cpu_set_register(state, reg1, reg1_v);
	}
	else if (reg1 == 32){
		err = mips_cpu_set_pc(state, reg1_v);
	}

	if (err != mips_Success){
		return err;
	}

	if (reg2 <= 31){
		err = mips_cpu_set_register(state, reg2, reg2_v);
	}
	else if (reg2 == 32){
		err = mips_cpu_set_pc(state, reg2_v);
	}

	if (err != mips_Success){
		return err;
	}


	uint32_t PC;
	mips_cpu_get_pc(state, &PC);

	uint8_t buffer[4];
	to_small_Endi(instr, buffer);
	err = mips_mem_write(mem, PC, 4, buffer);
	if (err != mips_Success){
		return err;
	}

	err = mips_cpu_step(state);

	//give priority to err_step
	bool err_step = false;
	if (err != mips_Success){
		err_step = true;
	}


	if (regRead <= 31){
		if (err_step){
			mips_cpu_get_register(state, regRead, &regRead_v);
		}
		else{
			err = mips_cpu_get_register(state, regRead, &regRead_v);
		}
	}
	else if (regRead == 32){
		if (err_step){
			mips_cpu_get_pc(state, &regRead_v);
		}
		else{
			err = mips_cpu_get_pc(state, &regRead_v);
		}
	}
	
	return err;
}

void test_mips_ADD(mips_cpu_h state, mips_mem_h mem){
	//ADD - R-type - Function 0x20 / d32

	//Test1 - Functionality
	int testId = mips_test_begin_test("ADD");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 1;
	uint32_t rt_v = 2;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 32);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 3), "Testing 1+2 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ADD");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, 0, 32);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 1+2 == 0 when rd = 0");

	//Test3 - Positive Overflow
	testId = mips_test_begin_test("ADD");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x7FFFFFFF;
	rt_v = 1;
	instr = R_type_instr(rs, rt, rd, 0, 32);
	uint32_t rd_before;
	mips_cpu_get_register(state, rd, &rd_before);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rd_v == rd_before), "Testing 0x7FFFFFF+1 == Overflow");

	//Test4 - Negative Overflow
	testId = mips_test_begin_test("ADD");
	rs = 5;
	rt = 6;
	rd = 4;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 0, 32);
	mips_cpu_get_register(state, rd, &rd_before);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rd_v == rd_before), "Testing 0x800000000+0x80000000 == Overflow");

	//Test5 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("ADD");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 32);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}

void test_mips_ADDI(mips_cpu_h state, mips_mem_h mem){
	//ADDI - I-type - Opcode 0x8 / d8

	//Test1 - Functionality
	int testId = mips_test_begin_test("ADDI");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 1;
	uint32_t imm = 2 ;
	uint32_t instr = I_type_instr(8, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 3), "Testing 1+2 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ADDI");
	rs = 5;
	rt = 0;
	rs_v = 1;
	imm = 2;
	instr = I_type_instr(8, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing 1+2 == 0 when rd = 0");

	//Test3 - Positive Overflow
	testId = mips_test_begin_test("ADDI");
	rs = 5;
	rt = 6;
	rs_v = 0x7FFFFFFF;
	imm = 1;
	instr = I_type_instr(8, rs, rt, imm);
	uint32_t rt_before;
	mips_cpu_get_register(state, rt, &rt_before);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rt_v == rt_before), "Testing 0x7FFFFFF+1 == Overflow");

	//Test4 - Negative Overflow
	testId = mips_test_begin_test("ADDI");
	rs = 5;
	rt = 6;
	rs_v = 0x80000000;
	imm = 0xFFFFFFFF;
	instr = I_type_instr(8, rs, rt, imm);
	mips_cpu_get_register(state, rt, &rt_before);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rt_v == rt_before), "Testing 0x800000000+0xFFFF == Overflow");
}

void test_mips_ADDIU(mips_cpu_h state, mips_mem_h mem){
	//ADDIU - I-type - Opcode 0x8 / d8

	//Test1 - Functionality
	int testId = mips_test_begin_test("ADDIU");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 1;
	uint32_t imm = 2;
	uint32_t instr = I_type_instr(9, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 3), "Testing 1+2 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ADDIU");
	rs = 5;
	rt = 0;
	rs_v = 1;
	imm = 2;
	instr = I_type_instr(9, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing 1+2 == 0 when rd = 0");

	//Test3 - Positive Overflow
	testId = mips_test_begin_test("ADDIU");
	rs = 5;
	rt = 6;
	rs_v = 0x7FFFFFFF;
	imm = 1;
	instr = I_type_instr(9, rs, rt, imm);
	uint32_t rt_before;
	mips_cpu_get_register(state, rt, &rt_before);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0x80000000), "Testing 0x7FFFFFF+1 == 0x80000000");

	//Test4 - Negative Overflow 
	testId = mips_test_begin_test("ADDIU");
	rs = 5;
	rt = 6;
	rs_v = 0x80000000;
	imm = 0x0000FFFF;
	instr = I_type_instr(9, rs, rt, imm);
	mips_cpu_get_register(state, rt, &rt_before);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0x7FFFFFFF), "Testing 0x800000000+0xFFFF == Overflow");
}

void test_mips_ADDU(mips_cpu_h state, mips_mem_h mem){
	//ADDU - R-type - Function 0x21 / d33

	//Test1 - Functionality
	int testId = mips_test_begin_test("ADDU");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 1;
	uint32_t rt_v = 2;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 33);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 3), "Testing 1+2 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, 0, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 1+2 == 0 when rd = 0");

	//Test3 - Positive Overflow 
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x7FFFFFFF;
	rt_v = 1;
	instr = R_type_instr(rs, rt, rd, 0, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x80000000), "Testing 0x7FFFFFF+1 == 0x80000000");

	//Test4 - Negative Overflow 
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 0, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0x80000000+0x80000000 == 0");

	//Test5 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");

}

void test_mips_SUB(mips_cpu_h state, mips_mem_h mem){
	//SUB - R-type - Function 0x20 / d32

	//Test1 - Functionality
	int testId = mips_test_begin_test("SUB");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 1;
	uint32_t rt_v = 2;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 34);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == -1), "Testing 1-2 == -1");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SUB");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, 0, 34);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 1-2 == 0 when rd = 0");

	//Test3 - Positive Overflow
	testId = mips_test_begin_test("SUB");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x7FFFFFFF;
	rt_v = 0xFFFFFFFF;
	instr = R_type_instr(rs, rt, rd, 0, 34);
	uint32_t rd_before;
	mips_cpu_get_register(state, rd, &rd_before);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rd_v == rd_before), "Testing 0x7FFFFFF-(-1) == Overflow");

	//Test4 - Negative Overflow
	testId = mips_test_begin_test("SUB");
	rs = 5;
	rt = 6;
	rd = 4;
	rs_v = 0x80000000;
	rt_v = 0x1;
	instr = R_type_instr(rs, rt, rd, 0, 34);
	mips_cpu_get_register(state, rd, &rd_before);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rd_v == rd_before), "Testing 0x800000000- 1 == Overflow");

	//Test5 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("SUB");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 34);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}

void test_mips_SUBU(mips_cpu_h state, mips_mem_h mem){
	//SUBU - R-type - Function 0x23 / d35

	//Test1 - Functionality
	int testId = mips_test_begin_test("SUBU");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 2;
	uint32_t rt_v = 1;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 35);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 1), "Testing 2-1 == 1");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, 0, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 1-2 == 0 when rd = 0");

	//Test3 - Positive Overflow 
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x7FFFFFFF;
	rt_v = -1;
	instr = R_type_instr(rs, rt, rd, 0, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x80000000), "Testing 0x7FFFFFF-(-1) == 0x80000000");

	//Test4 - Negative Overflow 
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 1;
	instr = R_type_instr(rs, rt, rd, 0, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x7FFFFFFF), "Testing 0x80000000-0x00000001 == 0x7FFFFFFF");

	//Test5 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");

}

void test_mips_AND(mips_cpu_h state, mips_mem_h mem){
	//AND - R-type - Function 0x24 / d36

	//Test1 - Functionality
	int testId = mips_test_begin_test("AND");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 0xF;
	uint32_t rt_v = 3;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 36);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 3), "Testing F & 3 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("AND");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 0xFF;
	rt_v = 0xEF;
	instr = R_type_instr(rs, rt, rd, 0, 36);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xFF & 0xEF == 0 when rd = 0");

	//Test3 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("AND");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 36);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}

void test_mips_ANDI(mips_cpu_h state, mips_mem_h mem){
	//ANDI - I-type - Opcode 0xC / d12

	//Test1 - Functionality
	int testId = mips_test_begin_test("ANDI");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 3;
	uint32_t imm = 0xF;
	uint32_t instr = I_type_instr(12, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 3), "Testing F & 3 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ANDI");
	rs = 5;
	rt = 0;
	rs_v = 0xF;
	imm = 3;
	instr = I_type_instr(12, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing F & 3 == 0 when rd = 0");
}

void test_mips_OR(mips_cpu_h state, mips_mem_h mem){
	//OR - R-type - Function 0x25 / d37

	//Test1 - Functionality
	int testId = mips_test_begin_test("OR");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 0xF;
	uint32_t rt_v = 3;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 37);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0xF), "Testing F | 3 == F");

	//Test2 - Modify $0
	testId = mips_test_begin_test("OR");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 0xFF;
	rt_v = 0xEF;
	instr = R_type_instr(rs, rt, rd, 0, 37);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xFF | 0xEF == 0 when rd = 0");

	//Test3 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("OR");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 37);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}

void test_mips_ORI(mips_cpu_h state, mips_mem_h mem){
	//ORI - I-type - Opcode 0xD / d12

	//Test1 - Functionality
	int testId = mips_test_begin_test("ORI");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 3;
	uint32_t imm = 0xF;
	uint32_t instr = I_type_instr(13, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0xF), "Testing F | 3 == F");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ORI");
	rs = 5;
	rt = 0;
	rs_v = 0xF;
	imm = 3;
	instr = I_type_instr(13, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing F | 3 == 0 when rd = 0");
}

void test_mips_XORI(mips_cpu_h state, mips_mem_h mem){
	//XORI - I-type - Opcode 0xE / d14

	//Test1 - Functionality
	int testId = mips_test_begin_test("XORI");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 3;
	uint32_t imm = 0xF;
	uint32_t instr = I_type_instr(14, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0xC), "Testing F ^ 3 == A");

	//Test2 - Modify $0
	testId = mips_test_begin_test("XORI");
	rs = 5;
	rt = 0;
	rs_v = 0xF;
	imm = 3;
	instr = I_type_instr(14, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing F ^ 3 == 0 when rd = 0");
}

void test_mips_XOR(mips_cpu_h state, mips_mem_h mem){
	//XOR - R-type - Function 0x26 / d38

	//Test1 - Functionality
	int testId = mips_test_begin_test("XOR");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 0xF;
	uint32_t rt_v = 3;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 38);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 12), "Testing F ^ 3 == b1100 (d12)");

	//Test2 - Modify $0
	testId = mips_test_begin_test("XOR");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 0xFF;
	rt_v = 0xEF;
	instr = R_type_instr(rs, rt, rd, 0, 38);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xFF ^ 0xEF == 0 when rd = 0");

	//Test3 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("XOR");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 38);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}

void test_mips_SLTU(mips_cpu_h state, mips_mem_h mem){
	//SLTU - R-type - Function 0x2B / d43

	//Test1 - Functionality TRUE
	int testId = mips_test_begin_test("SLTU");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 5;
	uint32_t rt_v = 6;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 43);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 1), "Testing  5 < 6 = set");

	//Test2 - Functionality False
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 7;
	rs_v = 6;
	rt_v = 5;
	instr = R_type_instr(rs, rt, rd, 0, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing  6 < 5 = not set");

	//Test3 - Modify $0
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 5;
	rt_v = 6;
	instr = R_type_instr(rs, rt, rd, 0, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing SLTU(true) when rd = 0");

	//Test4 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");

	//Test5 - Comparison is unsigned false
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = -1;
	rt_v = 1;
	instr = R_type_instr(rs, rt, rd, 0, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "-1 < 1 (0xFFFFFFFF < 0x1)  is false");

	//Test6 - Comparison is unsigned true
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 1;
	rt_v = -1;
	instr = R_type_instr(rs, rt, rd, 0, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 1), "1 < -1 (0x1 < 0xFFFFFFFF)  is true");
}

void test_mips_SLT(mips_cpu_h state, mips_mem_h mem){
	//SLT - R-type - Function 0x2A / d42

	//Test1 - Functionality TRUE
	int testId = mips_test_begin_test("SLT");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 5;
	uint32_t rt_v = 6;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 42);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 1), "Testing  5 < 6 = set");

	//Test2 - Functionality False
	testId = mips_test_begin_test("SLT");
	rs = 5;
	rt = 6;
	rd = 7;
	rs_v = 6;
	rt_v = 5;
	rd_v;
	instr = R_type_instr(rs, rt, rd, 0, 42);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing  6 < 5 = not set");

	//Test3 - Modify $0
	testId = mips_test_begin_test("SLT");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 5;
	rt_v = 6;
	instr = R_type_instr(rs, rt, rd, 0, 42);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing SLT(true) when rd = 0");

	//Test4 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("SLT");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 42);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");

	//Test5 - Comparison is Signed true
	testId = mips_test_begin_test("SLT");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = -1;
	rt_v = 1;
	instr = R_type_instr(rs, rt, rd, 0, 42);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 1), "-1 < 1 is true");

	//Test6 - Comparison is Signed False
	testId = mips_test_begin_test("SLT");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 1;
	rt_v = -1;
	instr = R_type_instr(rs, rt, rd, 0, 42);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "1 < -1 is false");
}

void test_mips_SLTI(mips_cpu_h state, mips_mem_h mem){
	//SLTI - I-type - Opcode 0xA / d10

	//Test1 - Functionality
	int testId = mips_test_begin_test("SLTI");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 3;
	uint32_t imm = 0x4;
	uint32_t instr = I_type_instr(10, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 1), "Testing 3 < 4 == true");

	//Test2 - Functionality
	testId = mips_test_begin_test("SLTI");
	rs = 5;
	rt = 6;
	rs_v = 4;
	imm = 0x3;
	instr = I_type_instr(10, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing 4 < 3 == false");

	//Test3 - Modify $0
	testId = mips_test_begin_test("SLTI");
	rs = 5;
	rt = 0;
	rs_v = 4;
	imm = 3;
	instr = I_type_instr(10, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing SLTI(true) == 0 when rd = 0");

	//Test4 - Comarison is signed (true)
	testId = mips_test_begin_test("SLTI");
	rs = 5;
	rt = 6;
	rs_v = -1;
	imm = 0x3;
	instr = I_type_instr(10, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 1), "Testing -1 < 3 == false");

	//Test5 - Comparison is signed (false)
	testId = mips_test_begin_test("SLTI");
	rs = 5;
	rt = 6;
	rs_v = 4;
	imm = -1;
	instr = I_type_instr(10, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing 4 < -1 == false");
}

void test_mips_SLTIU(mips_cpu_h state, mips_mem_h mem){
	//SLTIU - I-type - Opcode 0xB / d11

	//Test1 - Functionality
	int testId = mips_test_begin_test("SLTIU");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 3;
	uint32_t imm = 0x4;
	uint32_t instr = I_type_instr(11, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 1), "Testing 3 < 4 == true");

	//Test2 - Functionality
	testId = mips_test_begin_test("SLTIU");
	rs = 5;
	rt = 6;
	rs_v = 4;
	imm = 0x3;
	instr = I_type_instr(11, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing 4 < 3 == false");

	//Test3 - Modify $0
	testId = mips_test_begin_test("SLTIU");
	rs = 5;
	rt = 0;
	rs_v = 3;
	imm = 4;
	instr = I_type_instr(11, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing SLTIU(true) == 0 when rd = 0");

	//Test4 - Comarison is signed (true)
	testId = mips_test_begin_test("SLTIU");
	rs = 5;
	rt = 6;
	rs_v = -1;
	imm = 0x3;
	instr = I_type_instr(11, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing -1 < 3 (0xFFFFFFFF < 3) == false");

	//Test5 - Comparison is signed (false)
	testId = mips_test_begin_test("SLTIU");
	rs = 5;
	rt = 6;
	rs_v = 3;
	imm = -1;
	instr = I_type_instr(11, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 1), "Testing 3 < 0xFFFFFFFF (3 < 0xFFFFFFFF) == true");
}

void test_mips_LUI(mips_cpu_h state, mips_mem_h mem){
	//LUI - I-type - Opcode 0xF / d15

	//Test1 - Functionality
	int testId = mips_test_begin_test("LUI");
	uint32_t rs = 0;
	uint32_t rt = 6;
	uint32_t rt_v;
	uint32_t rs_v = 3;
	uint32_t imm = 0xCE;
	uint32_t instr = I_type_instr(15, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, rt, 0xFFFF, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0x00CE0000), "Testing LUI(0xCE) == 0x00CE0000");

	//Test2 - Modify $0
	testId = mips_test_begin_test("LUI");
	rs = 0;
	rt = 0;
	rs_v = 0xF;
	imm = 3;
	instr = I_type_instr(15, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rt_v == 0), "Testing F ^ 3 == 0 when rd = 0");

	//Test2 - Rs != 0 -> invalid instruction
	testId = mips_test_begin_test("LUI");
	rs = 5;
	rt = 1;
	rs_v = 0xF;
	imm = 3;
	instr = I_type_instr(15, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, rt, 1, instr, rt, rt_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction) && (rt_v == 1), "Testing F ^ 3 == 0 when rd = 0");
}

void test_mips_SLL(mips_cpu_h state, mips_mem_h mem){
	//SLL - R-type - Function 0x0 / d0

	//Test1 - Functionality
	int testId = mips_test_begin_test("SLL");
	uint32_t rs = 0;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t sa = 2;
	uint32_t rt_v = 1;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, sa, 0);
	mips_error err = set_step_read(state, rs, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 4), "Testing 1<<2 == 4");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SLL");
	rs = 0;
	rt = 6;
	rd = 0;
	sa = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, sa, 0);
	err = set_step_read(state, rs, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 1<<2 == 0 when rd = 0");

	//Test5 - Invalid instruction (Rs != 0) 
	testId = mips_test_begin_test("SLL");
	rs = 5;
	rt = 6;
	rd = 3;
	sa = 1;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 0);
	err = set_step_read(state, 33, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Rs != 0) ");
}

void test_mips_SRL(mips_cpu_h state, mips_mem_h mem){
	//SRL - R-type - Function 0x2 / d2

	//Test1 - Functionality
	int testId = mips_test_begin_test("SRL");
	uint32_t rs = 0;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t sa = 2;
	uint32_t rt_v = 0xF;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, sa, 2);
	mips_error err = set_step_read(state, rs, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 3), "Testing 0xF>>2 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SRL");
	rs = 0;
	rt = 6;
	rd = 0;
	sa = 1;
	rt_v = 0xF;
	instr = R_type_instr(rs, rt, rd, sa, 2);
	err = set_step_read(state, rs, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xF>>2 == 0 when rd = 0");

	//Test3 - Invalid instruction (Rs != 0) 
	testId = mips_test_begin_test("SRL");
	rs = 5;
	rt = 6;
	rd = 3;
	sa = 1;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 2);
	err = set_step_read(state, 33, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Rs != 0) ");

	//Test4 - No sign extend (Logical)
	testId = mips_test_begin_test("SRL");
	rs = 0;
	rt = 6;
	rd = 3;
	sa = 1;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 2);
	err = set_step_read(state, 33, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success)&&(rd_v==0x40000000), "0x800000000 >> 1 == 0x40000000 ");
}

void test_mips_SRLV(mips_cpu_h state, mips_mem_h mem){
	//SRLV - R-type - Function 0x6 / d6	

	//Test1 - Functionality
	int testId = mips_test_begin_test("SRLV");
	uint32_t rs = 1;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t sa = 0;
	uint32_t rt_v = 0xF;
	uint32_t rs_v = 0x1;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, sa, 6);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 7), "Testing 0xF>>1 == 7");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SRLV");
	rs = 1;
	rt = 6;
	rd = 0;
	sa = 0;
	rt_v = 0xF;
	rs_v = 0x1;
	instr = R_type_instr(rs, rt, rd, sa, 6);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xF>>2 == 0 when rd = 0");

	//Test3 - Invalid instruction (Sa != 0) 
	testId = mips_test_begin_test("SRLV");
	rs = 5;
	rt = 6;
	rd = 3;
	sa = 1;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 6);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Rs != 0) ");

	//Test4 - No sign extend (Logical)
	testId = mips_test_begin_test("SRLV");
	rs = 4;
	rt = 6;
	rd = 3;
	sa = 0;
	rt_v = 0x80000000;
	rs_v = 0x1;
	instr = R_type_instr(rs, rt, rd, sa, 6);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x40000000), "0x800000000 >> 1 == 0x40000000 ");

	//Test5 - Value in Rs > 31, shift = bottom 5 bits
	testId = mips_test_begin_test("SRLV");
	rs = 4;
	rt = 6;
	rd = 3;
	sa = 0;
	rt_v = 0xF;
	rs_v = 0xF01;
	instr = R_type_instr(rs, rt, rd, sa, 6);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x7), "0xF >> 1 == 0x7 when reg[rs]>31 but bottom 5 bits = 1 ");

}

void test_mips_SLLV(mips_cpu_h state, mips_mem_h mem){
	//SLLV - R-type - Function 0x4 / d4	

	//Test1 - Functionality
	int testId = mips_test_begin_test("SLLV");
	uint32_t rs = 1;
	uint32_t rt = 4;
	uint32_t rd = 7;
	uint32_t sa = 0;
	uint32_t rt_v = 0x2;
	uint32_t rs_v = 0x1;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, sa, 4);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 4), "Testing 0x2<<1 == 4");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SLLV");
	rs = 1;
	rt = 4;
	rd = 0;
	sa = 0;
	rt_v = 0xF;
	rs_v = 0x1;
	instr = R_type_instr(rs, rt, rd, sa, 4);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xF<<1 == 0 when rd = 0");

	//Test3 - Invalid instruction (Sa != 0) 
	testId = mips_test_begin_test("SLLV");
	rs = 5;
	rt = 4;
	rd = 3;
	sa = 1;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 4);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Rs != 0) ");

	//Test5 - Value in Rs > 31, shift = bottom 5 bits
	testId = mips_test_begin_test("SLLV");
	rs = 5;
	rt = 4;
	rd = 3;
	sa = 0;
	rt_v = 0x3;
	rs_v = 0xF01;
	instr = R_type_instr(rs, rt, rd, sa, 4);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x6), "0x3 << 1 == 0x6 when reg[rs]>31 but bottom 5 bits = 1 ");

}

void test_mips_SRAV(mips_cpu_h state, mips_mem_h mem){
	//SRAV - R-type - Function 0x7 / d7	

	//Test1 - Functionality
	int testId = mips_test_begin_test("SRAV");
	uint32_t rs = 1;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t sa = 0;
	uint32_t rt_v = 0xF;
	uint32_t rs_v = 0x1;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, sa, 7);
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 7), "Testing 0xF>>1 == 7");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SRAV");
	rs = 1;
	rt = 6;
	rd = 0;
	sa = 0;
	rt_v = 0xF;
	rs_v = 0x1;
	instr = R_type_instr(rs, rt, rd, sa, 7);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xF>>2 == 0 when rd = 0");

	//Test3 - Invalid instruction (Sa != 0) 
	testId = mips_test_begin_test("SRAV");
	rs = 5;
	rt = 7;
	rd = 3;
	sa = 1;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 7);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Rs != 0) ");

	//Test4 - Sign extend (Arithmeticm)
	testId = mips_test_begin_test("SRAV");
	rs = 4;
	rt = 6;
	rd = 3;
	sa = 0;
	rt_v = 0x80000000;
	rs_v = 0x1;
	instr = R_type_instr(rs, rt, rd, sa, 7);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0xC0000000), "0x800000000 >> 1 == 0xC0000000 ");

	//Test5 - Value in Rs > 31, shift = bottom 5 bits
	testId = mips_test_begin_test("SRAV");
	rs = 4;
	rt = 6;
	rd = 3;
	sa = 0;
	rt_v = 0xF;
	rs_v = 0xF01;
	instr = R_type_instr(rs, rt, rd, sa, 7);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x7), "0xF >> 1 == 0x7 when reg[rs]>31 but bottom 5 bits = 1 ");

}

void test_mips_SRA(mips_cpu_h state, mips_mem_h mem){
	//SRA - R-type - Function 0x3 / d3

	//Test1 - Functionality
	int testId = mips_test_begin_test("SRA");
	uint32_t rs = 0;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t sa = 3;
	uint32_t rt_v = 0xF;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, sa, 3);
	mips_error err = set_step_read(state, rs, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 1), "Testing 0xF>>3 == 1");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SRA");
	rs = 0;
	rt = 6;
	rd = 0;
	sa = 1;
	rt_v = 0xF;
	instr = R_type_instr(rs, rt, rd, sa, 3);
	err = set_step_read(state, rs, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xF>>1 == 0 when rd = 0");

	//Test3 - Invalid instruction (Rs != 0) 
	testId = mips_test_begin_test("SRA");
	rs = 5;
	rt = 6;
	rd = 3;
	sa = 1;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 3);
	err = set_step_read(state, 33, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Rs != 0) ");

	//Test4 - Sign extend
	testId = mips_test_begin_test("SRA");
	rs = 0;
	rt = 6;
	rd = 3;
	sa = 3;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, sa, 3);
	err = set_step_read(state, 33, 0, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0xF0000000), "0x800000000 >> 3 == 0xF0000000 ");
}

void test_mips_BLTZ(mips_cpu_h state, mips_mem_h mem){
	//BLTZ - I-type - Opcode 0x1 / d1 rs_v = 0

	//Test 1+2 - Functionality False (test 1 = PC after BLTZ is PCN) (test 2 = PC after PCN is PCN+4)
	int testId = mips_test_begin_test("BLTZ");
	uint32_t rs = 4;
	uint32_t rt = 0;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = 3;
	uint32_t imm = 10;
	uint32_t instr = I_type_instr(1, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before+4), "Testing step BLTZ(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BLTZ(false) PC = after delay slot");

	//Test 3+4 - Functionality True (test 1 = PC after BLTZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLTZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = -1;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLTZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm<<2))), "Testing second step BLTZ(true) PC = pc_delayslot + imm << 2");


	//Test 5+6 - Functionality False corner case 0 (test 1 = PC after BLTZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLTZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 0;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLTZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + 4)), "Testing second step BLTZ(true) PC = pc_delayslot + imm << 2");

	//Test 7+8 - Functionality True Negative immediate (test 1 = PC after BLTZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLTZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = -1;
	imm = 0x8001;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLTZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BLTZ(true) PC = pc_delayslot + imm << 2");

}

void test_mips_BLTZAL(mips_cpu_h state, mips_mem_h mem){
	//BLTZAL - I-type - Opcode 0x1 / d1 rs_v = 16

	//Test 1+2 - Functionality False (test 1 = PC after BLTZAL is PCN) (test 2 = PC after PCN is PCN+4)
	int testId = mips_test_begin_test("BLTZAL");
	uint32_t rs = 4;
	uint32_t rt = 16;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = 3;
	uint32_t imm = 10;
	uint32_t link = 0;
	uint32_t instr = I_type_instr(1, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BLTZAL(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BLTZAL(false) PC = after delay slot");

	//Test 3+4 - Functionality True (test 1 = PC after BLTZAL is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLTZAL");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = -1;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BLTZAL(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BLTZAL(true) PC = pc_delayslot + imm << 2");


	//Test 5+6 - Functionality False corner case 0 (test 1 = PC after BLTZAL is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLTZAL");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 0;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BLTZAL(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + 4)), "Testing second step BLTZAL(true) PC = pc_delayslot + imm << 2");

	//Test 6+7 - Functionality True Negative immediate (test 1 = PC after BLTZAL is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLTZAL");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = -1;
	imm = 0x8001;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BLTZAL(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLTZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BLTZAL(true) PC = pc_delayslot + imm << 2");

}

void test_mips_BLEZ(mips_cpu_h state, mips_mem_h mem){
	//BLEZ - I-type - Opcode 0x6 / d6

	//Test 1+2 - Functionality False (test 1 = PC after BLEZ is PCN) (test 2 = PC after PCN is PCN+4)
	int testId = mips_test_begin_test("BLEZ");
	uint32_t rs = 4;
	uint32_t rt = 0;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = 3;
	uint32_t imm = 10;
	uint32_t instr = I_type_instr(6, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLEZ(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BLEZ(false) PC = after delay slot");

	//Test 3+4 - Functionality True (test 1 = PC after BLEZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLEZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = -1;
	imm = 2;
	instr = I_type_instr(6, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLEZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BLEZ(true) PC = pc_delayslot + imm << 2");


	//Test 5+6 - Functionality True corner case 0 (test 1 = PC after BLEZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLEZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 0;
	imm = 2;
	instr = I_type_instr(6, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLEZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BLEZ(true) PC = pc_delayslot + imm << 2");

	//Test 7+8 - Functionality True Negative immediate (test 1 = PC after BLEZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BLEZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = -1;
	imm = 0x80000001;
	instr = I_type_instr(6, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLEZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BLEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BLEZ(true) PC = pc_delayslot + imm << 2");

	//Test 9 - Invalid Instruction rt_v != 0
	testId = mips_test_begin_test("BLEZ");
	rs = 4;
	rt = 2;
	rt = 1;
	PC = 0;
	rs_v = -1;
	imm = 0x8001;
	instr = I_type_instr(6, rs, rt, imm);
	mips_cpu_set_register(state, rt, 1);
	err = set_step_read(state, rs, rs_v, 32, PC, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction) && (PC == 0) , "Testing step BLEZ(true) PC = delay slot");
}

void test_mips_BGTZ(mips_cpu_h state, mips_mem_h mem){
	//BGTZ - I-type - Opcode 0x7 / d7

	//Test 1+2 - Functionality False (test 1 = PC after BGTZ is PCN) (test 2 = PC after PCN is PCN+4)
	int testId = mips_test_begin_test("BGTZ");
	uint32_t rs = 4;
	uint32_t rt = 0;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = -1;
	uint32_t imm = 10;
	uint32_t instr = I_type_instr(7, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BGTZ(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BGTZ(false) PC = after delay slot");

	//Test 3+4 - Functionality True (test 1 = PC after BGTZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGTZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	imm = 2;
	instr = I_type_instr(7, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BGTZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BGTZ(true) PC = pc_delayslot + imm << 2");


	//Test 5+6 - Functionality False corner case 0 (test 1 = PC after BGTZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGTZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 0;
	imm = 2;
	instr = I_type_instr(7, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BGTZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + 4)), "Testing second step BGTZ(true) PC = pc_delayslot + imm << 2");

	//Test 7+8 - Functionality True Negative immediate (test 1 = PC after BGTZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGTZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	imm = 0x8001;
	instr = I_type_instr(7, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BGTZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGTZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BGTZ(true) PC = pc_delayslot + imm << 2");

	//Test 9 - Invalid Instruction rt_v != 0
	testId = mips_test_begin_test("BGTZ");
	rs = 4;
	rt = 2;
	rt = 1;
	PC = 0;
	rs_v = -1;
	imm = 0x80000001;
	instr = I_type_instr(7, rs, rt, imm);
	mips_cpu_set_register(state, rt, 1);
	err = set_step_read(state, rs, rs_v, 32, PC, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction) && (PC == 0), "Testing step BGTZ(true) PC = delay slot");
}

void test_mips_BGEZ(mips_cpu_h state, mips_mem_h mem){
	//BGEZ - I-type - Opcode 0x1 / d1 - rs_v = 1

	//Test 1+2 - Functionality False (test 1 = PC after BGEZ is PCN) (test 2 = PC after PCN is PCN+4)
	int testId = mips_test_begin_test("BGEZ");
	uint32_t rs = 4;
	uint32_t rt = 1;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = -1;
	uint32_t imm = 2;
	uint32_t instr = I_type_instr(1, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BGEZ(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BGEZ(false) PC = after delay slot");

	//Test 3+4 - Functionality True (test 1 = PC after BGEZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGEZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BGEZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BGEZ(true) PC = pc_delayslot + imm << 2");

	//Test 5+6 - Functionality True Negative immediate (test 1 = PC after BLTZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGEZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 3;
	imm = 0x8001;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BLTZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BLTZ(true) PC = pc_delayslot + imm << 2");


	//Test  7+8 - Functionality True corner case 0 (test 1 = PC after BGEZ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGEZ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 0;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BGEZ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm<<2))), "Testing second step BGEZ(true) PC = pc_delayslot + imm << 2");

}

void test_mips_BGEZAL(mips_cpu_h state, mips_mem_h mem){
	//BGEZAL - I-type - Opcode 0x1 / d1 rs_v = 17

	//Test 1+2 - Functionality False (test 1 = PC after BGEZAL is PCN) (test 2 = PC after PCN is PCN+4)
	int testId = mips_test_begin_test("BGEZAL");
	uint32_t rs = 4;
	uint32_t rt = 17;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = -1;
	uint32_t imm = 2;
	uint32_t link = 0;
	uint32_t instr = I_type_instr(1, rs, rt, imm);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BGEZAL(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BGEZAL(false) PC = after delay slot");

	//Test 3+4 - Functionality True (test 1 = PC after BGEZAL is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGEZAL");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 2;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BGEZAL(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BGEZAL(true) PC = pc_delayslot + imm << 2");


	//Test 5+6 - Functionality True corner case 0 (test 1 = PC after BGEZAL is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGEZAL");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 0;
	imm = 2;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BGEZAL(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BGEZAL(true) PC = pc_delayslot + imm << 2");

	//Test 6+7 - Functionality True Negative immediate (test 1 = PC after BGEZAL is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BGEZAL");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	imm = 0x8001;
	instr = I_type_instr(1, rs, rt, imm);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_cpu_get_register(state, 31, &link);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4) && (link == PC_before + 8), "Testing step BGEZAL(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BGEZAL");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BGEZAL(true) PC = pc_delayslot + imm << 2");

}

void test_mips_BEQ(mips_cpu_h state, mips_mem_h mem){
	//BEQ - I-type - Opcode 0x4 / d4

	//Test 1+2 - Functionality False (test 1 = PC after BEQ is PCN) (test 2 = PC after PCN is PCN+4)
	int testId = mips_test_begin_test("BEQ");
	uint32_t rs = 4;
	uint32_t rt = 3;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = -1;
	uint32_t rt_v = 0;
	uint32_t imm = 10;
	uint32_t instr = I_type_instr(4, rs, rt, imm);
	mips_cpu_set_register(state, rt, rt_v);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BEQ(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BEQ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BEQ(false) PC = after delay slot");

	//Test 3+4 - Functionality True (test 1 = PC after BEQ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BEQ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	rt_v = 1;
	imm = 2;
	instr = I_type_instr(4, rs, rt, imm);
	mips_cpu_set_register(state, rt, rt_v);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BEQ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BEQ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BEQ(true) PC = pc_delayslot + imm << 2");


	//Test 5+6 - Functionality True Negative immediate (test 1 = PC after BEQ is PCN) (test 2 = PC after PCN is PCN+4)
	testId = mips_test_begin_test("BEQ");
	rs = 4;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	rt_v = 1;
	imm = 0x8001;
	instr = I_type_instr(4, rs, rt, imm);
	mips_cpu_set_register(state, rt, rt_v);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BEQ(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BEQ");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BEQ(true) PC = pc_delayslot + imm << 2");

}

void test_mips_BNE(mips_cpu_h state, mips_mem_h mem){
	//BNE - I-type - Opcode 0x5 / d5

	//Test 1+2 - Functionality False (test 1 = PC after BNE is PCN) (test 2 = PC after PCN is PCN+5)
	int testId = mips_test_begin_test("BNE");
	uint32_t rs = 5;
	uint32_t rt = 3;
	uint32_t PC;
	uint32_t PC_before = 0;
	uint32_t rs_v = -1;
	uint32_t rt_v = -1;
	uint32_t imm = 10;
	uint32_t instr = I_type_instr(5, rs, rt, imm);
	mips_cpu_set_register(state, rt, rt_v);
	mips_error err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BNE(false) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BNE");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing second step BNE(false) PC = after delay slot");

	//Test 3+5 - Functionality True (test 1 = PC after BNE is PCN) (test 2 = PC after PCN is PCN+5)
	testId = mips_test_begin_test("BNE");
	rs = 5;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	rt_v = 0;
	imm = 2;
	instr = I_type_instr(5, rs, rt, imm);
	mips_cpu_set_register(state, rt, rt_v);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BNE(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BNE");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + (imm << 2))), "Testing second step BNE(true) PC = pc_delayslot + imm << 2");


	//Test 5+6 - Functionality True Negative immediate (test 1 = PC after BNE is PCN) (test 2 = PC after PCN is PCN+5)
	testId = mips_test_begin_test("BNE");
	rs = 5;
	PC = 0;
	PC_before = 0;
	rs_v = 1;
	rt_v = 0;
	imm = 0x8001;
	instr = I_type_instr(5, rs, rt, imm);
	mips_cpu_set_register(state, rt, rt_v);
	err = set_step_read(state, rs, rs_v, 32, 0, instr, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == PC_before + 4), "Testing step BNE(true) PC = delay slot");
	PC_before = PC;
	testId = mips_test_begin_test("BNE");
	//Instruction set to 0 (NOP = shift 0 by 0) if this instruction doesnt work, test fails
	err = set_step_read(state, rs, rs_v, 33, 0, 0, 32, PC, mem);
	mips_test_end_test(testId, (err == mips_Success) && (PC == (PC_before + sign_extend18(imm << 2))), "Testing second step BNE(true) PC = pc_delayslot + imm << 2");

}

void test_mips_J(mips_cpu_h state, mips_mem_h mem){
	//J - J-type - Opcode 0x2 / d2

	//Test1 - Functionality1 (Jump from known pc and pcN)
	int testId = mips_test_begin_test("J");
	uint32_t target = 0;
	uint32_t PC_after;
	uint32_t instr = J_type_instr(true, target);

	//Set J instruction on PC = 0, PCN = 4
	mips_error err = set_step_read(state, 32, 0, 33, 3, instr, 32, PC_after, mem);

	//Execute delay slot instruction as NOP
	uint8_t buffer[4];
	to_small_Endi(R_type_instr(0, 0, 0, 0, 32), buffer);
	err = mips_mem_write(mem, PC_after, 4, buffer);

	if (err==mips_Success)
	err = mips_cpu_step(state);

	if (err == mips_Success)
	err = mips_cpu_get_pc(state, &PC_after);


	//Check adress is as expected (top 4 bits pcn(4) = 0 +target(0) = 0
	bool success = (err == mips_Success) && (PC_after == 0);
	mips_test_end_test(testId, success, "Jump from PC 0, target 0");
}

void test_mips_MF_MT_HI_LO(mips_cpu_h state, mips_mem_h mem){
	//MFHI - R-type - Function 0x10 / d16
	uint32_t rs = 0;
	uint32_t rt = 0;
	uint32_t rd = 1;
	uint32_t rs_v;
	uint32_t rt_v;
	uint32_t rd_v;
	uint32_t sa = 0;
	uint32_t instr;
	mips_error err;
	int testId;
	for (int i = 0; i <= 2; i++){
		switch (i){
		case 0:
			rs = 0;
			rt = 1;
			sa = 0;
			break;
		case 1:
			rs = 0;
			rt = 0;
			sa = 1;
			break;
		case 2:
			rs = 1;
			rt = 0;
			sa = 0;
			break;
		}
		instr = R_type_instr(rs, rt, rd, sa, 16);
		testId = mips_test_begin_test("MFHI");
		err = set_step_read(state, 33, 0, 33, 0, instr, 33, rd_v, mem);
		mips_test_end_test(testId, err = mips_ExceptionInvalidInstruction, "MFHI invalid rs/rt/sa");
	}

	//MTHI - R-type - Function 0x11 / d17
	rs = 0;
	for (int i = 0; i <= 2; i++){
		switch (i){
		case 0:
			rd = 0;
			rt = 1;
			sa = 0;
			break;
		case 1:
			rd = 0;
			rt = 0;
			sa = 1;
			break;
		case 2:
			rd = 1;
			rt = 0;
			sa = 0;
			break;
		}
		instr = R_type_instr(rs, rt, rd, sa, 17);
		testId = mips_test_begin_test("MTHI");
		err = set_step_read(state, 33, 0, 33, 0, instr, 33, rd, mem);
		mips_test_end_test(testId, err = mips_ExceptionInvalidInstruction, "MTHI invalid rd/rt/sa");
	}

	//MFLO - R-type - Function 0x12 / d18
	rd = 0;
	for (int i = 0; i <= 2; i++){
		switch (i){
		case 0:
			rs = 0;
			rt = 1;
			sa = 0;
			break;
		case 1:
			rs = 0;
			rt = 0;
			sa = 1;
			break;
		case 2:
			rs = 1;
			rt = 0;
			sa = 0;
			break;
		}
		instr = R_type_instr(rs, rt, rd, sa, 18);
		testId = mips_test_begin_test("MFLO");
		err = set_step_read(state, 33, 0, 33, 0, instr, 33, rd, mem);
		mips_test_end_test(testId, err = mips_ExceptionInvalidInstruction, "MFLO invalid rs/rt/sa");
	}

	//MTLO - R-type - Function 0x13 / d19
	rs = 1;
	for (int i = 0; i <= 2; i++){
		switch (i){
		case 0:
			rd = 0;
			rt = 1;
			sa = 0;
			break;
		case 1:
			rd = 0;
			rt = 0;
			sa = 1;
			break;
		case 2:
			rd = 1;
			rt = 0;
			sa = 0;
			break;
		}
		instr = R_type_instr(rs, rt, rd, sa, 19);
		testId = mips_test_begin_test("MTLO");
		err = set_step_read(state, 33, 0, 33, 0, instr, 33, rd, mem);
		mips_test_end_test(testId, err = mips_ExceptionInvalidInstruction, "MTLO invalid rs/rt/sa");
	}

	//Only way of testing MF and MT instructions are using one after the other,
	//therefore if one fails the test the other will as well

	//Test MTHI and MFHI

	//Set HI to 3
	testId = mips_test_begin_test("MTHI");
	rs = 1;
	rs_v = 3;
	rd = 0;
	rt = 0;
	sa = 0;
	instr = R_type_instr(rs, rt, rd, sa, 17);
	err = set_step_read(state, rs, rs_v, 33, 0, instr, 33, rd, mem);
	mips_test_end_test(testId, err == mips_Success, "MTHI success");

	//set rd to HI, check if 3
	testId = mips_test_begin_test("MFHI");
	rs = 0;
	rd = 1;
	rt = 0;
	sa = 0;
	instr = R_type_instr(rs, rt, rd, sa, 16);
	err = set_step_read(state, 33, 0, 33, 0, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v==3), "MFHI success, correct value");
	testId = mips_test_begin_test("MTHI");
	mips_test_end_test(testId, rd_v == 3, "MTHI success");

	//set rd=0 to HI, check remains 0
	testId = mips_test_begin_test("MFHI");
	rs = 0;
	rd = 0;
	rt = 0;
	sa = 0;
	instr = R_type_instr(rs, rt, rd, sa, 16);
	err = set_step_read(state, 33, 0, 33, 0, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "MFHI cannot change $0");

}

void test_mips_MULTU(mips_cpu_h state, mips_mem_h mem){
	//MULT - R-type - Function 0x19 / d25

	//Test 1+2 Fail on rd!=0 or sa!=0
	uint32_t rs = 0;
	uint32_t rt = 0;
	uint32_t rd = 1;
	uint32_t rs_v;
	uint32_t rt_v;
	uint32_t rd_v;
	uint32_t sa = 0;
	uint32_t instr;
	mips_error err;
	int testId;
	for (int i = 0; i <= 1; i++){
		switch (i){
		case 0:
			rd = 1;
			sa = 0;
			break;
		case 1:
			rd = 0;
			sa = 1;
			break;
		}
		instr = R_type_instr(rs, rt, rd, sa, 25);
		testId = mips_test_begin_test("MULTU");
		err = set_step_read(state, 33, 0, 33, 0, instr, 33, rd_v, mem);
		mips_test_end_test(testId, err = mips_ExceptionInvalidInstruction, "MULTU invalid rs/rt/sa");
	}

	testId = mips_test_begin_test("MULTU");
	rs = 1;
	rt = 2;
	rs_v = 2;
	rt_v = 3;
	rd = 0;
	sa = 0;
	instr = R_type_instr(rs, rt, rd, sa, 25);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, 33, rd_v, mem);
	bool success = (err == mips_Success);
	rd = 3;
	instr = R_type_instr(0, 0, rd, 0, 18);
	err = set_step_read(state, 33, rs_v, 33, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, success && (err==mips_Success)&&(rd==6), "MULTU 3*2");

}

//MULTU - R-type - Function 0x2 / d2
//MULT - R-type - Function 0x2 / d2
//DIVU - R-type - Function 0x2 / d2
//DIV - R-type - Function 0x2 / d2

void to_small_Endi(const uint32_t Data, uint8_t* output){
	output[0] = (Data >> 24) & 0xFF;
	output[1] = (Data >> 16) & 0xFF;
	output[2] = (Data >> 8) & 0xFF;
	output[3] = (Data >> 0) & 0xFF;
}

uint32_t sign_extend18(uint32_t in){
	uint32_t tmp = in;
	if ((in >> 17) == 1){
		return(tmp | 0xFFFC0000);
	}
	else{
		return tmp;
	}
}
