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
    return R(0b000000, rs, rt, rd, 0, 0b100000);
}