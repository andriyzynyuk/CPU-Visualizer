#include <gtest/gtest.h>
#include "Shifter.hpp"

TEST(ShifterTest, LeftShiftTest) {
    Wire Y(32), Direction(1), S(32);
    Shifter shifter(&Y, &Direction, S);

    // Test left shift: 1 << 1 = 2
    Y.set(1);
    Direction.set(1);  // Assume 1 = left
    shifter.eval();
    EXPECT_EQ(S.getValue(), 2);

    // Test left shift: 4 << 1 = 8
    Y.set(4);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 8);

    // Test left shift of larger number
    Y.set(0x7FFFFFFF);  // Max positive int
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0xFFFFFFFE);  // Shifted left, LSB 0
}

TEST(ShifterTest, RightShiftTest) {
    Wire Y(32), Direction(1), S(32);
    Shifter shifter(&Y, &Direction, S);

    // Test right shift: 2 >> 1 = 1
    Y.set(2);
    Direction.set(0);  // Assume 0 = right
    shifter.eval();
    EXPECT_EQ(S.getValue(), 1);

    // Test right shift: 8 >> 1 = 4
    Y.set(8);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 4);

    // Test right shift of larger number
    Y.set(0xFFFFFFFE);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0x7FFFFFFF);
}

TEST(ShifterTest, EdgeCases) {
    Wire Y(32), Direction(1), S(32);
    Shifter shifter(&Y, &Direction, S);

    // Left shift 0 -> 0
    Y.set(0);
    Direction.set(1);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0);

    // Right shift 0 -> 0
    Direction.set(0);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0);

    // Left shift max value loses MSB
    Y.set(0x80000000);  // Bit 31 set
    Direction.set(1);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0);  // Bit 31 shifts out

    // Right shift 1 -> 0
    Y.set(1);
    Direction.set(0);
    shifter.eval();
    EXPECT_EQ(S.getValue(), 0);
}