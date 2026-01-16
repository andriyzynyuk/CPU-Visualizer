#include <gtest/gtest.h>
#include "CPU.hpp"

TEST(CPUTEST, SingleInstructionTest) {
    CPU cpu;

    Instruction instruction = Instruction::ADDI(1, 0, 50);

    cpu.loadInstructions({instruction});
    cpu.firstCycle();

    EXPECT_EQ(cpu.regFile.registers[1], 50);
}

TEST(CPUTEST, ArithmeticInstructionTest) {
    CPU cpu;

    Instruction instruction0 = Instruction::ADDI(1, 0, 50);
    Instruction instruction1 = Instruction::ADDI(2, 0, 20);
    Instruction instruction2 = Instruction::ADD(3, 2, 1);
    Instruction instruction3 = Instruction::SUB(4, 3, 2);

    cpu.loadInstructions({instruction0, instruction1, instruction2, instruction3});
    cpu.firstCycle();
    cpu.executeCycle();
    cpu.executeCycle();
    cpu.executeCycle();

    EXPECT_EQ(cpu.regFile.registers[1], 50);
    EXPECT_EQ(cpu.regFile.registers[2], 20);
    EXPECT_EQ(cpu.regFile.registers[3], 70);
    EXPECT_EQ(cpu.regFile.registers[4], 50);
}

TEST(CPUTEST, LogicalInstructionTest) {
    CPU cpu;

    cpu.regFile.registers[0] = 0b10101010101010101010101010101010;
    cpu.regFile.registers[4] = 0b01010101010101010101010101010101;

    Instruction instruction0 = Instruction::NOR(2, 0, 1);
    Instruction instruction1 = Instruction::AND(3, 2, 2);
    Instruction instruction2 = Instruction::OR(5, 0, 4);
    Instruction instruction3 = Instruction::XOR(6, 2, 5);
    Instruction instruction4 = Instruction::ANDI(7, 5, 0);
    Instruction instruction5 = Instruction::ORI(8, 7, 0b1111111111111111);
    Instruction instruction6 = Instruction::XORI(9, 8, 0b1010101010101010);

    cpu.loadInstructions({instruction0, instruction1, instruction2, instruction3,
                            instruction4, instruction5, instruction6});
    cpu.firstCycle();
    cpu.executeCycle();
    cpu.executeCycle();
    cpu.executeCycle();
    cpu.executeCycle();
    cpu.executeCycle();
    cpu.executeCycle();

    EXPECT_EQ(cpu.regFile.registers[2], 0b01010101010101010101010101010101);
    EXPECT_EQ(cpu.regFile.registers[3], 0b01010101010101010101010101010101);
    EXPECT_EQ(cpu.regFile.registers[5], 0b11111111111111111111111111111111);
    EXPECT_EQ(cpu.regFile.registers[6], 0b10101010101010101010101010101010);
    EXPECT_EQ(cpu.regFile.registers[7], 0);
    EXPECT_EQ(cpu.regFile.registers[8], 0b11111111111111111111111111111111);
    EXPECT_EQ(cpu.regFile.registers[9], 0b00000000000000000101010101010101);
}