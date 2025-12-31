#include <gtest/gtest.h>
#include "Adder.hpp"

TEST(AdderTest, AdderAdditionTest) {
    Wire X(32);
    Wire Y(32);
    Wire C_IN(1);
    Wire SUM(32);
    Wire C_OUT(1);

    Adder adder(&X, &Y, &C_IN, SUM, C_OUT);

    X.set(100);
    Y.set(100);
    C_IN.set(0);

    adder.eval();

    EXPECT_EQ(SUM.getValue(), 200);
    EXPECT_EQ(C_OUT.getValue(), 0);

    X.set(4294967295u);
    Y.set(4294967295u);
    C_IN.set(0);

    adder.eval();

    EXPECT_EQ(SUM.getValue(), 4294967294u);
    EXPECT_EQ(C_OUT.getValue(), 1);

    X.set(4294967295);
    Y.set(4294967295);
    C_IN.set(1);

    adder.eval();

    EXPECT_EQ(SUM.getValue(), 0xFFFFFFFF);
    EXPECT_EQ(C_OUT.getValue(), 1);

    X.set(0);
    Y.set(0);
    C_IN.set(0);

    adder.eval();

    EXPECT_EQ(SUM.getValue(), 0);
    EXPECT_EQ(C_OUT.getValue(), 0);

    X.set(1);
    Y.set(0);
    C_IN.set(0);

    adder.eval();

    EXPECT_EQ(SUM.getValue(), 1);
    EXPECT_EQ(C_OUT.getValue(), 0);

    X.set(0);
    Y.set(0);
    C_IN.set(1);

    adder.eval();

    EXPECT_EQ(SUM.getValue(), 1);
    EXPECT_EQ(C_OUT.getValue(), 0);
}