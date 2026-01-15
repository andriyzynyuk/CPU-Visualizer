// AI Generated tests


#include <gtest/gtest.h>
#include "ControlUnit.hpp"

TEST(ControlUnitTest, ADDIInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test ADDI (0b001000)
    OP.set(0b001000);
    FN.set(0);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b1);
    EXPECT_EQ(RegDst.getValue(), 0b00);
    EXPECT_EQ(RegInSrc.getValue(), 0b01);
    EXPECT_EQ(ALUSrc.getValue(), 0b1);
    EXPECT_EQ(AddSub.getValue(), 0b0);
    EXPECT_EQ(FuncClass.getValue(), 0b10);
    EXPECT_EQ(DataRead.getValue(), 0b0);
    EXPECT_EQ(DataWrite.getValue(), 0b0);
    EXPECT_EQ(BrType.getValue(), 0b00);
    EXPECT_EQ(PCSrc.getValue(), 0b00);
}

TEST(ControlUnitTest, SLTIInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test SLTI (0b001010)
    OP.set(0b001010);
    FN.set(0);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b1);
    EXPECT_EQ(RegDst.getValue(), 0b00);
    EXPECT_EQ(RegInSrc.getValue(), 0b01);
    EXPECT_EQ(ALUSrc.getValue(), 0b1);
    EXPECT_EQ(AddSub.getValue(), 0b1);
    EXPECT_EQ(FuncClass.getValue(), 0b01);
    EXPECT_EQ(DataRead.getValue(), 0b0);
    EXPECT_EQ(DataWrite.getValue(), 0b0);
    EXPECT_EQ(BrType.getValue(), 0b00);
    EXPECT_EQ(PCSrc.getValue(), 0b00);
}

TEST(ControlUnitTest, ANDIInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test ANDI (0b001100)
    OP.set(0b001100);
    FN.set(0);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b1);
    EXPECT_EQ(RegDst.getValue(), 0b00);
    EXPECT_EQ(RegInSrc.getValue(), 0b01);
    EXPECT_EQ(ALUSrc.getValue(), 0b1);
    EXPECT_EQ(LogicFunc.getValue(), 0b00);
    EXPECT_EQ(FuncClass.getValue(), 0b11);
    EXPECT_EQ(DataRead.getValue(), 0b0);
    EXPECT_EQ(DataWrite.getValue(), 0b0);
    EXPECT_EQ(BrType.getValue(), 0b00);
    EXPECT_EQ(PCSrc.getValue(), 0b00);
}

TEST(ControlUnitTest, ORIInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test ORI (0b001101)
    OP.set(0b001101);
    FN.set(0);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b1);
    EXPECT_EQ(RegDst.getValue(), 0b00);
    EXPECT_EQ(RegInSrc.getValue(), 0b01);
    EXPECT_EQ(ALUSrc.getValue(), 0b1);
    EXPECT_EQ(LogicFunc.getValue(), 0b01);
    EXPECT_EQ(FuncClass.getValue(), 0b11);
}

TEST(ControlUnitTest, JUMPInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test JUMP (0b000010)
    OP.set(0b000010);
    FN.set(0);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b0);
    EXPECT_EQ(DataRead.getValue(), 0b0);
    EXPECT_EQ(DataWrite.getValue(), 0b0);
    EXPECT_EQ(PCSrc.getValue(), 0b01);
}

TEST(ControlUnitTest, BEQInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test BEQ (0b000100)
    OP.set(0b000100);
    FN.set(0);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b0);
    EXPECT_EQ(DataRead.getValue(), 0b0);
    EXPECT_EQ(DataWrite.getValue(), 0b0);
    EXPECT_EQ(BrType.getValue(), 0b01);
    EXPECT_EQ(PCSrc.getValue(), 0b00);
}

TEST(ControlUnitTest, ADDInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test ADD (R-type with FN = 0b100000)
    OP.set(0b000000);
    FN.set(0b100000);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b1);
    EXPECT_EQ(RegDst.getValue(), 0b01);
    EXPECT_EQ(RegInSrc.getValue(), 0b01);
    EXPECT_EQ(ALUSrc.getValue(), 0b0);
    EXPECT_EQ(AddSub.getValue(), 0b0);
    EXPECT_EQ(FuncClass.getValue(), 0b10);
}

TEST(ControlUnitTest, SUBInstruction) {
    Wire OP(6);
    Wire FN(6);
    Wire RegWrite(1);
    Wire RegDst(2);
    Wire RegInSrc(2);
    Wire ALUSrc(1);
    Wire AddSub(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire DataRead(1);
    Wire DataWrite(1);
    Wire BrType(2);
    Wire PCSrc(2);

    ControlUnit cu(&OP, &FN, RegWrite, RegDst, RegInSrc, ALUSrc,
                   AddSub, LogicFunc, FuncClass, DataRead, DataWrite, BrType, PCSrc);

    // Test SUB (R-type with FN = 0b100010)
    OP.set(0b000000);
    FN.set(0b100010);
    cu.eval();

    EXPECT_EQ(RegWrite.getValue(), 0b1);
    EXPECT_EQ(RegDst.getValue(), 0b01);
    EXPECT_EQ(RegInSrc.getValue(), 0b01);
    EXPECT_EQ(ALUSrc.getValue(), 0b0);
    EXPECT_EQ(AddSub.getValue(), 0b1);
    EXPECT_EQ(FuncClass.getValue(), 0b10);
}
