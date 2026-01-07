#include <gtest/gtest.h>
#include "Gates.hpp"

TEST(GatesTest, AndGateTest) {
    Wire in1(4);
    Wire in2(4);
    Wire out(4);
    
    AndGate gate({&in1, &in2}, out);

    in1.set(0b1010);
    in2.set(0b1100);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b1000);
}

TEST(GatesTest, OrGateTest) {
    Wire in1(4);
    Wire in2(4);
    Wire out(4);
    
    OrGate gate({&in1, &in2}, out);

    in1.set(0b1010);
    in2.set(0b1100);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b1110);
}

TEST(GatesTest, XorGateTest) {
    Wire in1(4);
    Wire in2(4);
    Wire out(4);
    
    XorGate gate({&in1, &in2}, out);

    in1.set(0b1010);
    in2.set(0b1100);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b0110);
}

TEST(GatesTest, NotGateTest) {
    Wire in1(4);
    Wire out(4);
    
    NotGate gate(&in1, out);

    in1.set(0b1010);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b0101);
}

TEST(GatesTest, NorGateTest) {
    Wire in1(4);
    Wire in2(4);
    Wire out(4);
    
    NorGate gate({&in1, &in2}, out);

    in1.set(0b1010);
    in2.set(0b1100);
    gate.eval();
    EXPECT_EQ(out.getValue(), 0b0001);
}