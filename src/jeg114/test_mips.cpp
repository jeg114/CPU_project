/*Computer architecture 2 - 2015 - Coursework 1
By: Jesús Erlantz García Condado
Username: jeg114
Date:17/10/2015
*/
#define _CRT_SECURE_NO_DEPRECATE
#include "mips.h"
#include "mips_internal.h"
#include < string > 
#include < iostream > 


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

void test_mips_ADD(mips_cpu_h state);
void test_mips_ADDU(mips_cpu_h state);
void test_mips_SUBU(mips_cpu_h state);
void test_mips_AND(mips_cpu_h state);
void test_mips_OR(mips_cpu_h state);
void test_mips_XOR(mips_cpu_h state);

mips_error set_step_read(mips_cpu_h state,
	const uint32_t& reg1,
	const uint32_t& reg1_v,
	const uint32_t& reg2,
	const uint32_t& reg2_v,
	const uint32_t& instr,
	const uint32_t& regRead,
	uint32_t& regRead_v,
	bool& no_change_regs);

int main(){

	mips_mem_h mem = mips_mem_create_ram(1024, 4);
	mips_cpu_h cpu = mips_cpu_create(mem);

	int debug;
	FILE* file_h = NULL;
	cout << "Set Debug level: " << endl;
	cin >> debug;
	if (debug > 0){
		string filename;
		cout << "Input file name for output / stderr / stdout, (if file not found it will be created)" << endl;
		cin >> filename;
		if (filename == "stderr"){
			file_h = stderr;
		}
		else if (filename == "stdout"){
			file_h = stdout;
		}
		else{
			file_h = fopen(filename.c_str(), "w");
		}
	}

	mips_cpu_set_debug_level(cpu, debug, file_h);

	mips_test_begin_suite();
	test_mips_ADD(cpu);
	test_mips_ADDU(cpu);
	test_mips_SUBU(cpu);
	test_mips_AND(cpu);
	test_mips_OR(cpu);
	mips_test_end_suite();

	cin >> debug;

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
		(imm << 0);

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
	bool& no_change_regs){


	mips_error err = mips_cpu_set_register(state, reg1, reg1_v);
	if (err != mips_Success){
		return err;
	}

	err= mips_cpu_set_register(state, reg2, reg2_v);
	if (err != mips_Success){
		return err;
	}

	//Save state of all registers to check if changed
	uint32_t tmp = 0;
	uint32_t regs_save[33];
	for (int i = 0; i <= 31; i++){
		err = mips_cpu_set_register(state, i, tmp);
		if (err != mips_Success){
			return err;
		}
		regs_save[i] = tmp;
	}

	uint32_t PC;
	mips_cpu_get_pc(state, &PC);

	regs_save[32] = state->pc;

	uint8_t buffer[4];
	to_small_Endi(instr, buffer);
	err = mips_mem_write(state->mem_handle, PC, 4, buffer);
	if (err != mips_Success){
		return err;
	}

	err = mips_cpu_step(state);

	if (err != mips_Success){
		return err;
	}

	no_change_regs = true;
	mips_cpu_get_pc(state, &PC);
	if (regs_save[32] != PC){
		no_change_regs = false;
	}
	int i = 0;
	while (no_change_regs && i <= 31){
		err = mips_cpu_set_register(state, i, tmp);
		if (err != mips_Success){
			return err;
		}
		if (regs_save[i] != tmp){
			no_change_regs = true;
		}
		i++;
	}



	if (regRead <= 31){
		err = mips_cpu_get_register(state, regRead, &regRead_v);
	}
	else if (regRead == 32){
		err = mips_cpu_get_pc(state, &regRead_v);
	}
	
	return err;
}

void test_mips_ADD(mips_cpu_h state){
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
	bool no_regs_changed;
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 3), "Testing 1+2 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ADD");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, 0, 32);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0) && no_regs_changed, "Testing 1+2 == 0 when rd = 0");

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
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rd_v == rd_before) && no_regs_changed, "Testing 0x7FFFFFF+1 == Overflow");

	//Test4 - Negative Overflow
	testId = mips_test_begin_test("ADD");
	rs = 5;
	rt = 6;
	rd = 4;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 0, 32);
	mips_cpu_get_register(state, rd, &rd_before);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionArithmeticOverflow) && (rd_v == rd_before) && no_regs_changed, "Testing 0x800000000+0x80000000 == Overflow");

	//Test5 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("ADD");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 32);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction) && no_regs_changed, "Invalid instruction (Shift != 0) ");
}

void test_mips_ADDU(mips_cpu_h state){
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
	bool no_regs_changed;
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 3), "Testing 1+2 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, 0, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 1+2 == 0 when rd = 0");

	//Test3 - Positive Overflow 
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x7FFFFFFF;
	rt_v = 1;
	instr = R_type_instr(rs, rt, rd, 0, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x80000000), "Testing 0x7FFFFFF+1 == 0x80000000");

	//Test4 - Negative Overflow 
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 0, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0x80000000+0x80000000 == 0");

	//Test5 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("ADDU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 33);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");

}

void test_mips_SUBU(mips_cpu_h state){
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
	bool no_regs_changed;
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 1), "Testing 2-1 == 1");

	//Test2 - Modify $0
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 1;
	rt_v = 2;
	instr = R_type_instr(rs, rt, rd, 0, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 1-2 == 0 when rd = 0");

	//Test3 - Positive Overflow 
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x7FFFFFFF;
	rt_v = -1;
	instr = R_type_instr(rs, rt, rd, 0, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x80000000), "Testing 0x7FFFFFF-(-1) == 0x80000000");

	//Test4 - Negative Overflow 
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 1;
	instr = R_type_instr(rs, rt, rd, 0, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0x7FFFFFFF), "Testing 0x80000000-0x00000001 == 0x7FFFFFFF");

	//Test5 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("SUBU");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 35);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");

}

void test_mips_AND(mips_cpu_h state){
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
	bool no_regs_changed;
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 3), "Testing F & 3 == 3");

	//Test2 - Modify $0
	testId = mips_test_begin_test("AND");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 0xFF;
	rt_v = 0xEF;
	instr = R_type_instr(rs, rt, rd, 0, 36);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xFF & 0xEF == 0 when rd = 0");

	//Test3 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("AND");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 36);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}

void test_mips_OR(mips_cpu_h state){
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
	bool no_regs_changed;
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0xF), "Testing F | 3 == F");

	//Test2 - Modify $0
	testId = mips_test_begin_test("OR");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 0xFF;
	rt_v = 0xEF;
	instr = R_type_instr(rs, rt, rd, 0, 37);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xFF | 0xEF == 0 when rd = 0");

	//Test3 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("OR");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 37);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}

void test_mips_XOR(mips_cpu_h state){
	//XOR - R-type - Function 0x26 / d38

	//Test1 - Functionality
	int testId = mips_test_begin_test("XOR");
	uint32_t rs = 5;
	uint32_t rt = 6;
	uint32_t rd = 7;
	uint32_t rs_v = 0xF;
	uint32_t rt_v = 3;
	uint32_t rd_v;
	uint32_t instr = R_type_instr(rs, rt, rd, 0, 37);
	bool no_regs_changed;
	mips_error err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 12), "Testing F ^ 3 == b1100 (d12)");

	//Test2 - Modify $0
	testId = mips_test_begin_test("XOR");
	rs = 5;
	rt = 6;
	rd = 0;
	rs_v = 0xFF;
	rt_v = 0xEF;
	instr = R_type_instr(rs, rt, rd, 0, 37);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_Success) && (rd_v == 0), "Testing 0xFF ^ 0xEF == 0 when rd = 0");

	//Test3 - Invalid instruction (Shift != 0) 
	testId = mips_test_begin_test("XOR");
	rs = 5;
	rt = 6;
	rd = 3;
	rs_v = 0x80000000;
	rt_v = 0x80000000;
	instr = R_type_instr(rs, rt, rd, 1, 37);
	err = set_step_read(state, rs, rs_v, rt, rt_v, instr, rd, rd_v, no_regs_changed);
	mips_test_end_test(testId, (err == mips_ExceptionInvalidInstruction), "Invalid instruction (Shift != 0) ");
}