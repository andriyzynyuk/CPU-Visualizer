#include <gtest/gtest.h>
#include "Gates.hpp"

TEST(GatesTest, AndGateTest) {
    Wire in1(32), in2(32), out(32);
    AndGate gate({&in1, &in2}, out);

    in1.set(0b1010);
    in2.set(0b1100);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b1000);

    in1.set(0xFFFFFFFF);
    in2.set(0xFFFFFFFF);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0xFFFFFFFF);

    in1.set(0);
    in2.set(0xFFFFFFFF);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0);
}

TEST(GatesTest, OrGateTest) {
    Wire in1(32), in2(32), out(32);
    OrGate gate({&in1, &in2}, out);

    in1.set(0b1010);
    in2.set(0b1100);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b1110);

    in1.set(0);
    in2.set(0);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0);

    in1.set(0xFFFFFFFF);
    in2.set(0);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0xFFFFFFFF);
}

TEST(GatesTest, XorGateTest) {
    Wire in1(32), in2(32), out(32);
    XorGate gate({&in1, &in2}, out);

    in1.set(0b1010);
    in2.set(0b1100);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b0110);

    in1.set(0xFFFFFFFF);
    in2.set(0xFFFFFFFF);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0);

    in1.set(0);
    in2.set(0);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0);
}

TEST(GatesTest, NotGateTest) {
    Wire in(32), out(32);
    NotGate gate(&in, out);

    in.set(0b1010);
    gate.eval();
    EXPECT_EQ(out.getValue(), ~0b1010u);

    in.set(0);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0xFFFFFFFF);

    in.set(0xFFFFFFFF);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0);
}