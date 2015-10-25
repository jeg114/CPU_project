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
uint32_t R_type_instr(std::string instr, uint32_t rs, uint32_t rt, uint32_t rd);

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
void test_mips_J(mips_cpu_h state, mips_mem_h mem);

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
	test_mips_SLTU(cpu, mem);
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
			mips_cpu_get_register(state, regRead, &regRead_v);
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
	//ADDI - I-type - Function 0x8 / d8

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
	//ADDIU - I-type - Function 0x8 / d8

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
	//ANDI - I-type - Function 0xC / d12

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
	//ORI - R-type - Function 0xD / d12

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
	//XORI - R-type - Function 0xE / d14

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

	//Test1 - Functionality False
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 7;
	rs_v = 6;
	rt_v = 5;
	rd_v;
	instr = R_type_instr(rs, rt, rd, 0, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing  6 < 5 = not set");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 5;
	rt_v = 6;
	instr = R_type_instr(rs, rt, rd, 0, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing SLTU(true) when rd = 0");

	//Test3 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("SLTU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 43);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, mem);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
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

void to_small_Endi(const uint32_t Data, uint8_t* output){
	output[0] = (Data >> 24) & 0xFF;
	output[1] = (Data >> 16) & 0xFF;
	output[2] = (Data >> 8) & 0xFF;
	output[3] = (Data >> 0) & 0xFF;
}