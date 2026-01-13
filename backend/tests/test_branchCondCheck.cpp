#include <gtest/gtest.h>
#include "BranchCondCheck.hpp"

TEST(BranchCondCheckTest, BEQTrueTest) {
    Wire rt(32);
    Wire rs(32);
    Wire BrType(1);
    
    Wire BrTrue(1);
    
    BranchCondCheck bcc(&rt, &rs, &BrType, BrTrue);

    rt.set(1);
    rs.set(1);
    BrType.set(0);
    bcc.eval();
    EXPECT_EQ(BrTrue.getValue(), 1);
}

TEST(BranchCondCheckTest, BEQFalseTest) {
    Wire rt(32);
    Wire rs(32);
    Wire BrType(1);
    
    Wire BrTrue(1);
    
    BranchCondCheck bcc(&rt, &rs, &BrType, BrTrue);

    rt.set(0);
    rs.set(1);
    BrType.set(0);
    bcc.eval();
    EXPECT_EQ(BrTrue.getValue(), 0);
}

TEST(BranchCondCheckTest, BNETrueTest) {
    Wire rt(32);
    Wire rs(32);
    Wire BrType(1);
    
    Wire BrTrue(1);
    
    BranchCondCheck bcc(&rt, &rs, &BrType, BrTrue);

    rt.set(0);
    rs.set(1);
    BrType.set(1);
    bcc.eval();
    EXPECT_EQ(BrTrue.getValue(), 1);
}

TEST(BranchCondCheckTest, BNEFalseTest) {
    Wire rt(32);
    Wire rs(32);
    Wire BrType(1);
    
    Wire BrTrue(1);
    
    BranchCondCheck bcc(&rt, &rs, &BrType, BrTrue);

    rt.set(1);
    rs.set(1);
    BrType.set(1);
    bcc.eval();
    EXPECT_EQ(BrTrue.getValue(), 0);
}
