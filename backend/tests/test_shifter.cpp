#include <gtest/gtest.h>
#include "Shifter.hpp"

TEST(ShifterTest, RightShiftTest) {
    Wire Y(32);
    Wire Direction(1);
    Wire S(32);
    Shifter shifter(&Y, &Direction, S);

    Direction.set(0);

    Y.set(2);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 1);

    Y.set(8);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 4);
}

TEST(ShifterTest, LeftShiftTest) {
    Wire Y(32);
    Wire Direction(1);
    Wire S(32);
    
    Shifter shifter(&Y, &Direction, S);

    Direction.set(1);

    Y.set(1);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 2);

    Y.set(4);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 8);
}