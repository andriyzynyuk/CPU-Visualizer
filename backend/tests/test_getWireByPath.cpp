#include <gtest/gtest.h>
#include "CPU.hpp"

TEST(GetWireByPathTest, stringTest) {
    CPU cpu;

    Instruction instruction = Instruction::ADDI(1, 0, 50);

    cpu.loadInstructions({instruction});
    cpu.firstCycle();

    EXPECT_EQ(cpu.getWireByPath("regFile.registers[1]"), 50);
    EXPECT_EQ(cpu.getWireByPath("alu.x"), 0);
    EXPECT_EQ(cpu.getWireByPath("alu.y"), 50);
    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[1]"), 1);
}