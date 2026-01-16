#pragma once

#include <cstdint>

struct Instruction {
    uint32_t raw = 0;

    static uint32_t mask(int bits);
    void setBits(int shift, int bits, uint32_t value);
    uint32_t getBits(int shift, int bits) const;

    // decoders
    uint8_t op() const;
    uint8_t rs() const;
    uint8_t rt() const;
    uint8_t rd() const;
    uint8_t sh() const;
    uint8_t fn() const;
    uint16_t imm() const;
    uint32_t jta() const;

    // builders
    static Instruction R(uint8_t op, uint8_t rs, uint8_t rt,
                         uint8_t rd, uint8_t sh, uint8_t fn);

    static Instruction I(uint8_t op, uint8_t rs, uint8_t rt, uint16_t imm);
    static Instruction J(uint8_t op, uint32_t jta);

    // instructions
    //static Instruction LUI(uint8_t rt, uint8_t imm);
    static Instruction ADD(uint8_t rd, uint8_t rs, uint8_t rt);
    static Instruction SUB(uint8_t rd, uint8_t rs, uint8_t rt);
    static Instruction SLT(uint8_t rd, uint8_t rs, uint8_t rt);
    static Instruction ADDI(uint8_t rt, uint8_t rs, uint16_t imm);
    static Instruction SLTI(uint8_t rt, uint8_t rs, uint16_t imm);
    static Instruction AND(uint8_t rd, uint8_t rs, uint8_t rt);
    static Instruction OR(uint8_t rd, uint8_t rs, uint8_t rt);
    static Instruction XOR(uint8_t rd, uint8_t rs, uint8_t rt);
    static Instruction NOR(uint8_t rd, uint8_t rs, uint8_t rt);
    static Instruction ANDI(uint8_t rt, uint8_t rs, uint16_t imm);
    static Instruction ORI(uint8_t rt, uint8_t rs, uint16_t imm);
    static Instruction XORI(uint8_t rt, uint8_t rs, uint16_t imm);
    //static Instruction LW(uint8_t rt, uint8_t rs, uint16_t imm);
    //static Instruction SW(uint8_t rt, uint8_t rs, uint16_t imm);
    static Instruction JUMP(uint32_t jta);
    static Instruction JR(uint8_t rs);
    static Instruction BLTZ(uint8_t rs, uint16_t imm);
    static Instruction BEQ(uint8_t rt, uint8_t rs, uint16_t imm);
    static Instruction BNE(uint8_t rt, uint8_t rs, uint16_t imm);
    static Instruction JAL(uint32_t jta);
    //static Instruction SYSCALL();
    
    
};