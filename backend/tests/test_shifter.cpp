#include <gtest/gtest.h>
#include "Shifter.hpp"

TEST(ShifterTest, LogicalLeftShiftTest) {
    Wire Y(32);
    Wire Amount(5);
    Wire Func(2);
    Wire S(32);
    
    Shifter shifter(&Y, &Amount, &Func, S);

    Amount.set(1);
    Func.set(0b01);

    Y.set(1);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 2);

    Y.set(4);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 8);

    Y.set(0b10000000000000000000000000000001);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 2);
}

TEST(ShifterTest, LogicalRightShiftTest) {
    Wire Y(32);
    Wire Amount(5);
    Wire Func(2);
    Wire S(32);
    
    Shifter shifter(&Y, &Amount, &Func, S);
    Amount.set(1);
    Func.set(0b10);

    Y.set(2);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 1);

    Y.set(32);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 16);

    Y.set(0b10000000000000000000000000000001);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 1073741824);
}

TEST(ShifterTest, ArithmeticRightShiftTest) {
    Wire Y(32);
    Wire Amount(5);
    Wire Func(2);
    Wire S(32);
    
    Shifter shifter(&Y, &Amount, &Func, S);
    Amount.set(1);
    Func.set(0b11);

    Y.set(0b10000000000000000000000000000000);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0b11000000000000000000000000000000);

    Y.set(0b11110000000000000000000000000000);
    Amount.set(4);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0b11111111000000000000000000000000);

    Y.set(-16);
    Amount.set(2);
    shifter.eval();
    EXPECT_EQ(S.getValue(), -4);
}