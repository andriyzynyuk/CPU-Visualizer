#include <gtest/gtest.h>
#include "FullAdder.hpp"

TEST(FullAdderTest, AdditionTest) {
    Wire X(1);
    Wire Y(1);
    Wire C_IN(1);
    Wire SUM(1);
    Wire C_OUT(1);

    FullAdder fullAdder(&X, &Y, &C_IN, SUM, C_OUT);

    X.set(0b0);
    Y.set(0b0);
    C_IN.set(0b0);
    fullAdder.eval();

    EXPECT_EQ(SUM.getValue(), 0b0);
    EXPECT_EQ(C_OUT.getValue(), 0b0);

    X.set(0b1);
    Y.set(0b0);
    C_IN.set(0b0);
    fullAdder.eval();

    EXPECT_EQ(SUM.getValue(), 0b1);
    EXPECT_EQ(C_OUT.getValue(), 0b0);

    X.set(0b0);
    Y.set(0b1);
    C_IN.set(0b0);
    fullAdder.eval();

    EXPECT_EQ(SUM.getValue(), 0b1);
    EXPECT_EQ(C_OUT.getValue(), 0b0);

    X.set(0b0);
    Y.set(0b0);
    C_IN.set(0b1);
    fullAdder.eval();

    EXPECT_EQ(SUM.getValue(), 0b1);
    EXPECT_EQ(C_OUT.getValue(), 0b0);

    X.set(0b1);
    Y.set(0b0);
    C_IN.set(0b1);
    fullAdder.eval();

    EXPECT_EQ(SUM.getValue(), 0b0);
    EXPECT_EQ(C_OUT.getValue(), 0b1);

    X.set(0b1);
    Y.set(0b1);
    C_IN.set(0b1);
    fullAdder.eval();

    EXPECT_EQ(SUM.getValue(), 0b1);
    EXPECT_EQ(C_OUT.getValue(), 0b1);

    X.set(0b0);
    Y.set(0b0);
    C_IN.set(0b1);
    fullAdder.eval();

    EXPECT_EQ(SUM.getValue(), 0b1);
    EXPECT_EQ(C_OUT.getValue(), 0b0);
}