#include <gtest/gtest.h>
#include "ALU.hpp"

TEST(ALUTest, ALUShifterTest) {
    Wire X(32);
    Wire Y(32);
    Wire AddSub(1);
    Wire ShiftDirection(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ShiftDirection, &LogicFunc, &FuncClass, S, Cout);

    X.set(0);
    AddSub.set(0);
    LogicFunc.set(0);
    FuncClass.set(0);

    // Y = 0 Test
    Y.set(0);
    ShiftDirection.set(0);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0);

    // Shift Right Test
    Y.set(4);
    ShiftDirection.set(0);
    alu.eval();
    EXPECT_EQ(S.getValue(), 2);

    // Shift Left Test
    Y.set(2);
    ShiftDirection.set(1);
    alu.eval();
    EXPECT_EQ(S.getValue(), 4);

    // Shift Out of Bounds Test
    Y.set(1);
    ShiftDirection.set(0); // Shift right
    alu.eval();
    EXPECT_EQ(S.getValue(), 0);
}

TEST(ALUTest, ALUSetLessThanTest) {
    Wire X(32);
    Wire Y(32);
    Wire AddSub(1);
    Wire ShiftDirection(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ShiftDirection, &LogicFunc, &FuncClass, S, Cout);

    AddSub.set(1);
    ShiftDirection.set(0);
    LogicFunc.set(0);
    FuncClass.set(1);

    // X < Y Test
    X.set(100);
    Y.set(200);
    alu.eval();
    EXPECT_EQ(S.getValue(), 0xFFFFFFFF);

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
    Wire ShiftDirection(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ShiftDirection, &LogicFunc, &FuncClass, S, Cout);

    // Test addition
    X.set(100);
    Y.set(100);
    AddSub.set(0);
    ShiftDirection.set(0);
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
    Wire ShiftDirection(1);
    Wire LogicFunc(2);
    Wire FuncClass(2);
    Wire S(32);
    Wire Cout(1);

    ALU alu(&X, &Y, &AddSub, &ShiftDirection, &LogicFunc, &FuncClass, S, Cout);

    X.set(0b01010101010101010101010101010101);
    Y.set(0b00000000000000001111111111111111);
    AddSub.set(0);
    ShiftDirection.set(0);
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