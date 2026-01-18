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

// AI test
TEST(GetWireByPathTest, addi_internal_and_nested_paths) {
    CPU cpu;
    cpu.loadInstructions({Instruction::ADDI(1, 0, 50)});
    cpu.firstCycle();

    // Internal CPU wires after ADDI
    EXPECT_EQ(cpu.getWireByPath("imm"), 50);
    EXPECT_EQ(cpu.getWireByPath("imm_se"), 50);
    EXPECT_EQ(cpu.getWireByPath("rt"), 1);
    EXPECT_EQ(cpu.getWireByPath("rs"), 0);

    // ALU values
    EXPECT_EQ(cpu.getWireByPath("ALU_out"), 50);
    EXPECT_EQ(cpu.getWireByPath("alu.xPlusY"), 50);
    EXPECT_EQ(cpu.getWireByPath("alu.s"), 50);

    // MUX paths (ALUSrc selects immediate for ADDI)
    EXPECT_EQ(cpu.getWireByPath("ALUSrc_MUX.input0"), 0);
    EXPECT_EQ(cpu.getWireByPath("ALUSrc_MUX.input1"), 50);
    EXPECT_EQ(cpu.getWireByPath("ALUSrc_MUX.out"), 50);

    // NextAddr paths
    EXPECT_EQ(cpu.getWireByPath("nextAddr.adder.cin"), 1);
    EXPECT_EQ(cpu.getWireByPath("IncrPC"), 1);
    EXPECT_EQ(cpu.getWireByPath("nextAddr.IncrPC"), 1);

    // RegFile writeback confirmed
    EXPECT_EQ(cpu.getWireByPath("regFile.registers[1]"), 50);
}

TEST(GetWireByPathTest, nested_bit_access_and_bounds) {
    CPU cpu;
    cpu.loadInstructions({Instruction::ADDI(1, 0, 50)});
    cpu.firstCycle();

    // Bit checks for Y (50 = 32 + 16 + 2)
    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[1]"), 1);
    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[4]"), 1);
    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[5]"), 1);

    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[0]"), 0);
    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[2]"), 0);
    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[3]"), 0);

    // Out of range indices should return -1
    EXPECT_EQ(cpu.getWireByPath("alu.adder.Y_bits[32]"), (uint32_t)-1);
    EXPECT_EQ(cpu.getWireByPath("alu.adder.sum_bits[33]"), (uint32_t)-1);
}

TEST(GetWireByPathTest, unknown_path_returns_minus_one) {
    CPU cpu;
    cpu.loadInstructions({Instruction::ADDI(1, 0, 50)});
    cpu.firstCycle();
    EXPECT_EQ(cpu.getWireByPath("unknown.component"), (uint32_t)-1);
}