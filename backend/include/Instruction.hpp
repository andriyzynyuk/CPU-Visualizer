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
    static Instruction ADD(uint8_t rd, uint8_t rs, uint8_t rt);
};