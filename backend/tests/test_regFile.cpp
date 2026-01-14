#include <gtest/gtest.h>
#include "RegFile.hpp"

TEST(RegFileTest, SetRegTest) {
    Wire rs(5);
    Wire rt(5);
    Wire writeData(5);
    Wire regIn(32);
    Wire regWrite(1);
    
    Wire rs_out(32);
    Wire rt_out(32);

    RegFile regFile(&rs, &rt, &writeData, &regIn, &regWrite,
                        rs_out, rt_out);

    // Write to Reg with regWrite disabled
    rs.set(0);
    rt.set(0);
    writeData.set(1);
    regIn.set(53);
    regWrite.set(0);

    regFile.eval();
    EXPECT_EQ(rs_out.getValue(), 0);
    EXPECT_EQ(rt_out.getValue(), 0);

    // Write to Reg with RegWrite enabled
    rs.set(1);
    rt.set(0);
    writeData.set(1);
    regIn.set(53);
    regWrite.set(1);

    regFile.eval();
    EXPECT_EQ(rs_out.getValue(), 0);
    EXPECT_EQ(rt_out.getValue(), 0);

    // Grab Value of Reg 1
    rs.set(1);
    rt.set(0);
    writeData.set(1);
    regIn.set(228); // Set Random Value here
    regWrite.set(1);

    regFile.eval();
    EXPECT_EQ(rs_out.getValue(), 53);
    EXPECT_EQ(rt_out.getValue(), 0);
}