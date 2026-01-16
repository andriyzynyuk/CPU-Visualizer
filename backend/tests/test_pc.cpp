#include <gtest/gtest.h>
#include "PC.hpp"

TEST(PCTest, PCInitialization) {
    Wire pc_in(30);
    Wire pc_out(30);
    
    PC pc(&pc_in, pc_out);

    EXPECT_EQ(pc.reg, 0);
}

TEST(PCTest, PCEval) {
    Wire pc_in(30);
    Wire pc_out(30);
    
    PC pc(&pc_in, pc_out);
    
    pc_in.set(100);
    pc.eval();
    EXPECT_EQ(pc.reg, 100);
}
