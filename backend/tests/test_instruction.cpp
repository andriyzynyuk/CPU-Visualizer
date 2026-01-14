#include <gtest/gtest.h>
#include "Instruction.hpp"

TEST(InstructionTest, GetSetBits) {
    Instruction i;

    i.setBits(0, 5, 0b10101);
    EXPECT_EQ(i.getBits(0, 5), 0b10101);

    i.setBits(5, 5, 0b11011);
    EXPECT_EQ(i.getBits(5, 5), 0b11011);
    EXPECT_EQ(i.getBits(0, 5), 0b10101);
}

TEST(InstructionTest, RType) {
    Instruction i = Instruction::R(0b000001, 1, 2, 3, 4, 0b000010);

    EXPECT_EQ(i.op(), 0b000001);
    EXPECT_EQ(i.rs(), 1);
    EXPECT_EQ(i.rt(), 2);
    EXPECT_EQ(i.rd(), 3);
    EXPECT_EQ(i.sh(), 4);
    EXPECT_EQ(i.fn(), 0b000010);
}

TEST(InstructionTest, IType) {
    Instruction i = Instruction::I(0b000010, 5, 6, 0b1111000011110000);

    EXPECT_EQ(i.op(), 0b000010);
    EXPECT_EQ(i.rs(), 5);
    EXPECT_EQ(i.rt(), 6);
    EXPECT_EQ(i.imm(), 0b1111000011110000);
}

TEST(InstructionTest, JType) {
    Instruction i = Instruction::J(0b000011, 0b11111111111111111111111111);

    EXPECT_EQ(i.op(), 0b000011);
    EXPECT_EQ(i.jta(), 0b11111111111111111111111111);
}

TEST(InstructionTest, ADD) {
    Instruction i = Instruction::ADD(7, 8, 9);
    
    EXPECT_EQ(i.op(), 0b000000);
    EXPECT_EQ(i.rs(), 8);
    EXPECT_EQ(i.rt(), 9);
    EXPECT_EQ(i.rd(), 7);
    EXPECT_EQ(i.sh(), 0);
    EXPECT_EQ(i.fn(), 0b100000);
}