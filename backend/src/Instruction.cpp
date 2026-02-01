#include "Instruction.hpp"

uint32_t Instruction::mask(int bits) {
    return (1u << bits) - 1;
}

void Instruction::setBits(int shift, int bits, uint32_t value) {
    raw &= ~(mask(bits) << shift);
    raw |= (value & mask(bits)) << shift;
}

uint32_t Instruction::getBits(int shift, int bits) const {
    return (raw >> shift) & mask(bits);
}

uint8_t Instruction::op() const  { return getBits(26, 6); }
uint8_t Instruction::rs() const  { return getBits(21, 5); }
uint8_t Instruction::rt() const  { return getBits(16, 5); }
uint8_t Instruction::rd() const  { return getBits(11, 5); }
uint8_t Instruction::sh() const  { return getBits(6, 5); }
uint8_t Instruction::fn() const  { return getBits(0, 6); }
uint16_t Instruction::imm() const { return getBits(0, 16); }
uint32_t Instruction::jta() const { return getBits(0, 26); }

Instruction Instruction::R(uint8_t op, uint8_t rs, uint8_t rt,
                           uint8_t rd, uint8_t sh, uint8_t fn) {
    Instruction i;
    i.setBits(26, 6, op);
    i.setBits(21, 5, rs);
    i.setBits(16, 5, rt);
    i.setBits(11, 5, rd);
    i.setBits(6,  5, sh);
    i.setBits(0,  6, fn);
    return i;
}

Instruction Instruction::I(uint8_t op, uint8_t rs, uint8_t rt, uint16_t imm) {
    Instruction i;
    i.setBits(26, 6, op);
    i.setBits(21, 5, rs);
    i.setBits(16, 5, rt);
    i.setBits(0, 16, imm);
    return i;
}

Instruction Instruction::J(uint8_t op, uint32_t jta) {
    Instruction i;
    i.setBits(26, 6, op);
    i.setBits(0, 26, jta);
    return i;
}

Instruction Instruction::ADD(uint8_t rd, uint8_t rs, uint8_t rt) {
    return R(0, rs, rt, rd, 0, 0b100000);
}

Instruction Instruction::SUB(uint8_t rd, uint8_t rs, uint8_t rt) {
    return R(0, rs, rt, rd, 0, 0b100010);
}

Instruction Instruction::SLT(uint8_t rd, uint8_t rs, uint8_t rt) {
    return R(0, rs, rt, rd, 0, 0b101010);
}

Instruction Instruction::ADDI(uint8_t rt, uint8_t rs, uint16_t imm) {
    return I(0b001000, rs, rt, imm);
}

Instruction Instruction::SLTI(uint8_t rt, uint8_t rs, uint16_t imm) {
    return I(0b001010, rs, rt, imm);
}

Instruction Instruction::AND(uint8_t rd, uint8_t rs, uint8_t rt) {
    return R(0, rs, rt, rd, 0, 0b100100);
}

Instruction Instruction::OR(uint8_t rd, uint8_t rs, uint8_t rt) {
    return R(0, rs, rt, rd, 0, 0b100101);
}

Instruction Instruction::XOR(uint8_t rd, uint8_t rs, uint8_t rt) {
    return R(0, rs, rt, rd, 0, 0b100110);
}

Instruction Instruction::NOR(uint8_t rd, uint8_t rs, uint8_t rt) {
    return R(0, rs, rt, rd, 0, 0b100111);
}

Instruction Instruction::ANDI(uint8_t rt, uint8_t rs, uint16_t imm) {
    return I(0b001100, rs, rt, imm);
}

Instruction Instruction::ORI(uint8_t rt, uint8_t rs, uint16_t imm) {
    return I(0b001101, rs, rt, imm);
}

Instruction Instruction::XORI(uint8_t rt, uint8_t rs, uint16_t imm) {
    return I(0b001110, rs, rt, imm);
}

Instruction Instruction::JUMP(uint32_t jta) {
    return J(0b000010, jta);
}

Instruction Instruction::JR(uint8_t rs) {
    return R(0, rs, 0, 0, 0, 0b001000);
}

Instruction Instruction::BLTZ(uint8_t rs, uint16_t imm) {
    return I(0b000001, rs, 0, imm);
}

Instruction Instruction::BEQ(uint8_t rt, uint8_t rs, uint16_t imm) {
    return I(0b000100, rs, rt, imm);
}

Instruction Instruction::BNE(uint8_t rt, uint8_t rs, uint16_t imm) {
    return I(0b000101, rs, rt, imm);
}

Instruction Instruction::JAL(uint32_t jta) {
    return J(0b000011, jta);
}

Instruction Instruction::SLL(uint8_t rd, uint8_t rt, uint8_t sh) {
    return R(0, 0, rt, rd, sh, 0);
}
Instruction Instruction::SRL(uint8_t rd, uint8_t rt, uint8_t sh) {
    return R(0, 0, rt, rd, sh, 0b000010);
}
Instruction Instruction::SRA(uint8_t rd, uint8_t rt, uint8_t sh) {
    return R(0, 0, rt, rd, sh, 0b000011);
}
Instruction Instruction::SLLV(uint8_t rd, uint8_t rt, uint8_t rs) {
    return R(0, rs, rt, rd, 0, 0b000100);
}
Instruction Instruction::SRLV(uint8_t rd, uint8_t rt, uint8_t rs) {
    return R(0, rs, rt, rd, 0, 0b000110);
}
Instruction Instruction::SRAV(uint8_t rd, uint8_t rt, uint8_t rs) {
    return R(0, rs, rt, rd, 0, 0b000111);
}
// Instruction Instruction::SYSCALL() {
//     return R(0, 0, 0, 0, 0, 0b001100);
// }