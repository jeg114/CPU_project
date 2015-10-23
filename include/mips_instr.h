#ifndef mips__instr
#define mips_instr

#include "mips_cpu.h"

#ifdef __cplusplus
extern "C"{
#endif

//BLTZ Branch on less than zero  Type: I Difficulty: 3 XXX Opcode: 1 
mips_error BLTZ(mips_cpu_h state, uint8_t rs, uint16_t imm);

//BGEZ Branch on greater than or equal to zero  Type: I Difficulty: 3 XXX Opcode: 1 
mips_error BGEZ(mips_cpu_h state, uint8_t rs, uint16_t imm);

//BLTZAL Branch on less than zero and link  Type: I Difficulty: 4 XXXX Opcode: 1 
mips_error BLTZAL(mips_cpu_h state, uint8_t rs, uint16_t imm);

//BGEZAL Branch on non-negative (>=0) and link  Type: I Difficulty: 4 XXXX Opcode: 1 
mips_error BGEZAL(mips_cpu_h state, uint8_t rs, uint16_t imm);

//BEQ Branch on equal  Type: I Difficulty: 3 XXX Opcode: 4 
mips_error BEQ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//BNE Branch on not equal  Type: I Difficulty: 3 XXX Opcode: 5 
mips_error BNE(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//BLEZ Branch on less than or equal to zero  Type: I Difficulty: 3 XXX Opcode: 6 
mips_error BLEZ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//BGTZ Branch on greater than zero  Type: I Difficulty: 3 XXX Opcode: 7 
mips_error BGTZ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//ADDI Add immediate (with overflow)  Type: I Difficulty: 2 XX Opcode: 8 
mips_error ADDI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//ADDIU Add immediate unsigned (no overflow)  Type: I Difficulty: 2 XX Opcode: 9 
mips_error ADDIU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//SLTI Set on less than immediate (signed)  Type: I Difficulty: 3 XXX Opcode: 9 
mips_error SLTI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//SLTIU Set on less than immediate unsigned  Type: I Difficulty: 3 XXX Opcode: B 
mips_error SLTIU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//ANDI Bitwise and immediate  Type: I Difficulty: 2 XX Opcode: C 
mips_error ANDI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//ORI Bitwise or immediate  Type: I Difficulty: 2 XX Opcode: D 
mips_error ORI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//XORI Bitwise exclusive or immediate  Type: I Difficulty: 2 XX Opcode: E 
mips_error XORI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LUI Load upper immediate  Type: I Difficulty: 2 XX Opcode: 0F 
mips_error LUI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LB Load byte  Type: I Difficulty: 3 XXX Opcode: 20 
mips_error LB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LH Load half-word  Type: I Difficulty: 3 XXX Opcode: 21 
mips_error LH(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LWL Load word left  Type: I Difficulty: 5 XXXXX Opcode: 22 
mips_error LWL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LW Load word  Type: I Difficulty: 2 XX Opcode: 23 
mips_error LW(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LBU Load byte unsigned  Type: I Difficulty: 3 XXX Opcode: 24 
mips_error LBU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LHU Load half-word unsigned  Type: I Difficulty: 3 XXX Opcode: 25 
mips_error LHU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//LWR Load word right  Type: I Difficulty: 5 XXXXX Opcode: 26 
mips_error LWR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//SB Store byte  Type: I Difficulty: 3 XXX Opcode: 28 
mips_error SB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//SH Store half-word  Type: I Difficulty: 3 XXX Opcode: 29 
mips_error SH(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//SW Store word  Type: I Difficulty: 2 XX Opcode: 2B 
mips_error SW(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm);

//J Jump  Type: J Difficulty: 3 XXX Opcode: 2 
mips_error J(mips_cpu_h state, uint32_t target);

//JAL Jump and link  Type: J Difficulty: 4 XXXX Opcode: 3 
mips_error JAL(mips_cpu_h state, uint32_t target);

//SLL Shift left logical  Type: R Difficulty: 2 XX Opcode: 0 
mips_error SLL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SRL Shift right logical  Type: R Difficulty: 2 XX Opcode: 2 
mips_error SRL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SRA Shift right arithmetic  Type: R Difficulty: 2 XX Opcode: 3 
mips_error SRA(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SLLV Shift left logical variable  Type: R Difficulty: 3 XX Opcode: 4 
mips_error SLLV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SRLV Shift right logical variable  Type: R Difficulty: 2 XX Opcode: 6 
mips_error SRLV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SRAV Shift right arithmetic  Type: R Difficulty: 2 XX Opcode: 7 
mips_error SRAV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//JR Jump register  Type: R Difficulty: 3 XXX Opcode: 8 
mips_error JR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//JALR Jump and link register  Type: R Difficulty: 4 XXXX Opcode: 9 
mips_error JALR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//MFHI Move from HI  Type: R Difficulty: 3 XXXX Opcode: 10 
mips_error MFHI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//MTHI Move to HI  Type: R Difficulty: 3 XXXX Opcode: 11 
mips_error MTHI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//MFLO Move from LO  Type: R Difficulty: 3 XXXX Opcode: 12 
mips_error MFLO(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//MTLO Move to LO  Type: R Difficulty: 3 XXXX Opcode: 13 
mips_error MTLO(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//MULT Multiply  Type: R Difficulty: 4 XXXX Opcode: 18 
mips_error MULT(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//MULTU Multiply unsigned  Type: R Difficulty: 3 XXXX Opcode: 19 
mips_error MULTU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//DIV Divide  Type: R Difficulty: 4 XXXX Opcode: 1A 
mips_error DIV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//DIVU Divide unsigned  Type: R Difficulty: 3 XXXX Opcode: 1B 
mips_error DIVU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//ADD Add (with overflow)  Type: R Difficulty: 2 XX Opcode: 20 
mips_error ADD(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//ADDU Add unsigned (no overflow)  Type: R Difficulty: 1 X Opcode: 21 
mips_error ADDU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SUB Subtract  Type: R Difficulty: 2 XX Opcode: 22 
mips_error SUB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SUBU Subtract unsigned  Type: R Difficulty: 1 X Opcode: 23 
mips_error SUBU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//AND Bitwise and  Type: R Difficulty: 1 X Opcode: 24 
mips_error AND(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//OR Bitwise or  Type: R Difficulty: 1 X Opcode: 25 
mips_error OR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//XOR Bitwise exclusive or  Type: R Difficulty: 1 X Opcode: 26 
mips_error XOR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SLT Set on less than (signed)  Type: R Difficulty: 2 XX Opcode: 2A 
mips_error SLT(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

//SLTU Set on less than unsigned  Type: R Difficulty: 1 X Opcode: 2B 
mips_error SLTU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa);

uint32_t sign_extend(uint16_t in);

bool is_positive(uint32_t in);


#ifdef __cplusplus
};
#endif

#endif