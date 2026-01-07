#include <gtest/gtest.h>
#include "MUX.hpp"

TEST(MUXTest, MUX4to1Test) {
    Wire IN0(1);
    Wire IN1(1);
    Wire IN2(1);
    Wire IN3(1);
    Wire S1(1);
    Wire S0(1);
    Wire OUT(1);

    MUX4to1 mux(&IN0, &IN1, &IN2, &IN3, &S1, &S0, OUT);

    // Test S1=0, S0=0 -> OUT = IN0
    IN0.set(1);
    IN1.set(0);
    IN2.set(1);
    IN3.set(0);
    
    // Select 00
    S1.set(0);
    S0.set(0);
    mux.eval();
    EXPECT_EQ(OUT.getValue(), 1);

    // Select 01
    S1.set(0);
    S0.set(1);
    mux.eval();
    EXPECT_EQ(OUT.getValue(), 0);

    // Select 10
    S1.set(1);
    S0.set(0);
    mux.eval();
    EXPECT_EQ(OUT.getValue(), 1);

    // Select 11
    S1.set(1);
    S0.set(1);
    mux.eval();
    EXPECT_EQ(OUT.getValue(), 0);
}

TEST(MUXTest, MUX2to1Test) {
    Wire IN0(1);
    Wire IN1(1);
    Wire S0(1);
    Wire OUT(1);

    MUX2to1 mux(&IN0, &IN1, &S0, OUT);

    IN0.set(1);
    IN1.set(0);

    // Select 0
    S0.set(0);
    mux.eval();
    EXPECT_EQ(OUT.getValue(), 1);

    // Select 1
    S0.set(1);
    mux.eval();
    EXPECT_EQ(OUT.getValue(), 0);
}