#include <gtest/gtest.h>
#include "ALU.hpp"

TEST(ALUTest, ALUShifterTest) {
    Wire X(32);
    Wire Y(32);
    Wire AddSub(1);
    Wire ConstAmount(5);
    Wire ConstVar(1);
    Wire ShiftFunc(2);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ConstAmount, &ConstVar, &ShiftFunc, &LogicFunc, &FuncClass, S, Cout);

    AddSub.set(0);
    LogicFunc.set(0);
    FuncClass.set(0);

    // Shifter Disabled Test
    Y.set(10);
    X.set(1);
    ConstAmount.set(5);
    ConstVar.set(0b0);
    ShiftFunc.set(0b00);
    alu.eval();
    EXPECT_EQ(S.getValue(), 10);

    // Shift Left Logical Const Test
    Y.set(10);
    X.set(2);
    ConstAmount.set(1);
    ConstVar.set(0b0);
    ShiftFunc.set(0b01);
    alu.eval();
    EXPECT_EQ(S.getValue(), 20);

    // Shift Left Logical Var Test
    Y.set(10);
    X.set(1);
    ConstAmount.set(2);
    ConstVar.set(0b1);
    ShiftFunc.set(0b01);
    alu.eval();
    EXPECT_EQ(S.getValue(), 20);

    // Shift Right Logical Const Test
    Y.set(10);
    X.set(2);
    ConstAmount.set(1);
    ConstVar.set(0b0);
    ShiftFunc.set(0b10);
    alu.eval();
    EXPECT_EQ(S.getValue(), 5);

    // Shift Right Logical Var Test
    Y.set(10);
    X.set(1);
    ConstAmount.set(2);
    ConstVar.set(0b1);
    ShiftFunc.set(0b10);
    alu.eval();
    EXPECT_EQ(S.getValue(), 5);

    // Shift Right Arithmetic Positive Test
    Y.set(10);
    ConstAmount.set(1);
    ConstVar.set(0b0);
    ShiftFunc.set(0b11);
    alu.eval();
    EXPECT_EQ(S.getValue(), 5);

    // Shift Right Arithmetic Negative Test
    Y.set(-10);
    ConstAmount.set(1);
    ConstVar.set(0b0);
    ShiftFunc.set(0b11);
    alu.eval();
    EXPECT_EQ(S.getValue(), -5);
}

TEST(ALUTest, ALUSetLessThanTest) {
    Wire X(32);
    Wire Y(32);
    Wire AddSub(1);
    Wire ConstAmount(5);
    Wire ConstVar(1);
    Wire ShiftFunc(2);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ConstAmount, &ConstVar, &ShiftFunc, &LogicFunc, &FuncClass, S, Cout);

    AddSub.set(1);
    ConstAmount.set(0);
    ConstVar.set(0);
    ShiftFunc.set(0);
    LogicFunc.set(0);
    FuncClass.set(1);

    // X < Y Test
    X.set(100);
    Y.set(200);
    alu.eval();
    EXPECT_EQ(S.getValue(), 1);

    // X = Y Test
    X.set(200);
    Y.set(200);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0);

    // X > Y Test
    X.set(201);
    Y.set(200);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0);
}

TEST(ALUTest, ALUAdderTest) {
    Wire X(32);
    Wire Y(32);
    Wire AddSub(1);
    Wire ConstAmount(5);
    Wire ConstVar(1);
    Wire ShiftFunc(2);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ConstAmount, &ConstVar, &ShiftFunc, &LogicFunc, &FuncClass, S, Cout);

    // Test addition
    X.set(100);
    Y.set(100);
    AddSub.set(0);
    ConstAmount.set(0);
    ConstVar.set(0);
    ShiftFunc.set(0);
    LogicFunc.set(0);
    FuncClass.set(2);
    alu.eval();
    EXPECT_EQ(S.getValue(), 200);
    EXPECT_EQ(Cout.getValue(), 0);

    // Test subtraction
    AddSub.set(1);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0);
    EXPECT_EQ(Cout.getValue(), 1);
}

TEST(ALUTest, ALULogicTest) {
    Wire X(32);
    Wire Y(32);
    Wire AddSub(1);
    Wire ConstAmount(5);
    Wire ConstVar(1);
    Wire ShiftFunc(2);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ConstAmount, &ConstVar, &ShiftFunc, &LogicFunc, &FuncClass, S, Cout);

    X.set(0b01010101010101010101010101010101);
    Y.set(0b00000000000000001111111111111111);
    AddSub.set(0);
    ConstAmount.set(0);
    ConstVar.set(0);
    ShiftFunc.set(0);
    FuncClass.set(3);

    // Test AND
    LogicFunc.set(0);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0b00000000000000000101010101010101);

    // Test OR
    LogicFunc.set(1);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0b01010101010101011111111111111111);

    // Test XOR
    LogicFunc.set(2);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0b01010101010101011010101010101010);

    // Test NOR
    LogicFunc.set(3);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0b10101010101010100000000000000000);
}