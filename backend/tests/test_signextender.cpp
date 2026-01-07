#include <gtest/gtest.h>
#include "SignExtender.hpp"

TEST(SignExtenderTest, PositiveExtension) {
    Wire input(1);
    Wire output(32);

    SignExtender se(&input, output);

    // Extend 0 Test
    input.set(0);
    se.eval();
    EXPECT_EQ(output.getValue(), 0);
}

TEST(SignExtenderTest, NegativeExtension) {
    Wire input(1);
    Wire output(32);

    SignExtender se(&input, output);

    // Extend 1 Test
    input.set(1);
    se.eval();
    EXPECT_EQ(output.getValue(), 0xFFFFFFFF);
}

TEST(SignExtenderTest, DifferentSizes) {
    Wire input4(4);
    Wire output(32);

    SignExtender se(&input4, output);

    // Positive Extenstion Test
    input4.set(0b0111);
    se.eval();
    EXPECT_EQ(output.getValue(), 0b00000000000000000000000000000111);

    // Negative Extenstion Test
    input4.set(0b1000);
    se.eval();
    EXPECT_EQ(output.getValue(), 0b11111111111111111111111111111000);
}