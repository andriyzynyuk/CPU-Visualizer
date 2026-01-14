#include <gtest/gtest.h>
#include "InstrCache.hpp"

TEST(InstrCacheTest, GetInstruction) {
    Wire pc(30);
    Wire instr(32);

    InstrCache cache(&pc, instr);

    std::vector<Instruction> program;
    program.push_back(Instruction::ADD(1, 2, 3)); // ADD $1, $2, $3
    program.push_back(Instruction::I(0b001000, 4, 5, 100)); // ADDI $4, $5, 100
    program.push_back(Instruction::J(0b000010, 0x123456)); // J 0x123456

    cache.setInstructions(program);

    // get first instruction
    pc.set(0);
    cache.eval();
    EXPECT_EQ(instr.getValue(), program[0].raw);

    // get second
    pc.set(1);
    cache.eval();
    EXPECT_EQ(instr.getValue(), program[1].raw);

    // get third
    pc.set(2);
    cache.eval();
    EXPECT_EQ(instr.getValue(), program[2].raw);
}