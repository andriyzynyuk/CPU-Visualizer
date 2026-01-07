#include <gtest/gtest.h>
#include "LogicUnit.hpp"

TEST(LUTest, LogicOperationsTest) {
    Wire X(32);
    Wire Y(32);
    Wire LogicFunc(2);
    Wire S(32);

    LogicUnit lu(&X, &Y, &LogicFunc, S);

    X.set(0b01010101010101010101010101010101);
    Y.set(0b00000000000000001111111111111111);

    // Test AND
    LogicFunc.set(0);
    lu.eval();
    EXPECT_EQ(S.getValue(), 0b00000000000000000101010101010101);

    // Test OR
    LogicFunc.set(1);
    lu.eval();
    EXPECT_EQ(S.getValue(), 0b01010101010101011111111111111111);

    // Test XOR
    LogicFunc.set(2);
    lu.eval();
    EXPECT_EQ(S.getValue(), 0b01010101010101011010101010101010);

    // Test NOR
    LogicFunc.set(3);
    lu.eval();
    EXPECT_EQ(S.getValue(), 0b10101010101010100000000000000000);
}