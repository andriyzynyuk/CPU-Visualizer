#include <gtest/gtest.h>
#include "Wire.hpp"

TEST(WireTest, MaskingWorks) {
    Wire w(4);
    w.set(0b111111);

    EXPECT_EQ(w.getValue(), 0b1111);
}

TEST(WireTest, GetBit) {
    Wire w(4);
    w.set(0b1010);

    EXPECT_EQ(w.getBit(1), 1);
    EXPECT_EQ(w.getBit(0), 0);
}