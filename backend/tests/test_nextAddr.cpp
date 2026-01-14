#include <gtest/gtest.h>
#include "NextAddr.hpp"

TEST(NextAddrTest, IncrPCTest) {
    Wire rt(32);
    Wire rs(32);
    Wire pc(30);
    Wire jta(26);
    Wire sysCallAddr(30);
    Wire BrType(2);
    Wire PCSrc(2);
    
    Wire incrPC(30);
    Wire nextPC(30);

    NextAddr nextAddr(&rt, &rs, &pc, &jta, &sysCallAddr,
                        &BrType, &PCSrc, incrPC, nextPC);

    rt.set(0);
    rs.set(0);
    pc.set(1);
    jta.set(0);
    sysCallAddr.set(0);
    BrType.set(0);
    PCSrc.set(0);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 2);
    EXPECT_EQ(nextPC.getValue(), 2);
}

TEST(NextAddrTest, BranchTest) {
    Wire rt(32);
    Wire rs(32);
    Wire pc(30);
    Wire jta(26);
    Wire sysCallAddr(30);
    Wire BrType(2);
    Wire PCSrc(2);
    
    Wire incrPC(30);
    Wire nextPC(30);

    NextAddr nextAddr(&rt, &rs, &pc, &jta, &sysCallAddr,
                        &BrType, &PCSrc, incrPC, nextPC);

    // BEQ TRUE
    rt.set(1);
    rs.set(1);
    pc.set(10);
    jta.set(5);
    sysCallAddr.set(0);
    BrType.set(1);
    PCSrc.set(0);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 16);
    EXPECT_EQ(nextPC.getValue(), 16);

    // BEQ FALSE
    rt.set(0);
    rs.set(1);
    pc.set(10);
    jta.set(5);
    sysCallAddr.set(0);
    BrType.set(1);
    PCSrc.set(0);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 11);
    EXPECT_EQ(nextPC.getValue(), 11);

    // BNE TRUE
    rt.set(0);
    rs.set(1);
    pc.set(10);
    jta.set(5);
    sysCallAddr.set(0);
    BrType.set(2);
    PCSrc.set(0);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 16);
    EXPECT_EQ(nextPC.getValue(), 16);

    // BNE FALSE
    rt.set(1);
    rs.set(1);
    pc.set(10);
    jta.set(5);
    sysCallAddr.set(0);
    BrType.set(2);
    PCSrc.set(0);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 11);
    EXPECT_EQ(nextPC.getValue(), 11);
}

TEST(NextAddrTest, JumpTest) {
    Wire rt(32);
    Wire rs(32);
    Wire pc(30);
    Wire jta(26);
    Wire sysCallAddr(30);
    Wire BrType(2);
    Wire PCSrc(2);
    
    Wire incrPC(30);
    Wire nextPC(30);

    NextAddr nextAddr(&rt, &rs, &pc, &jta, &sysCallAddr,
                        &BrType, &PCSrc, incrPC, nextPC);

    rt.set(0);
    rs.set(1);
    pc.set(0b110011111111111111111111111111);
    jta.set(0b10101010101010101010101010);
    sysCallAddr.set(0);
    BrType.set(0);
    PCSrc.set(1);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 0b110011111111111111111111111111+1);
    EXPECT_EQ(nextPC.getValue(), 0b110010101010101010101010101010);
}

TEST(NextAddrTest, JumpRegisterTest) {
    Wire rt(32);
    Wire rs(32);
    Wire pc(30);
    Wire jta(26);
    Wire sysCallAddr(30);
    Wire BrType(2);
    Wire PCSrc(2);
    
    Wire incrPC(30);
    Wire nextPC(30);

    NextAddr nextAddr(&rt, &rs, &pc, &jta, &sysCallAddr,
                        &BrType, &PCSrc, incrPC, nextPC);

    rt.set(0);
    rs.set(0b10101010101010101010101010101011);
    pc.set(1);
    jta.set(0);
    sysCallAddr.set(0);
    BrType.set(0);
    PCSrc.set(2);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 2);
    EXPECT_EQ(nextPC.getValue(), 0b101010101010101010101010101010);
}

TEST(NextAddrTest, SysCallTest) {
    Wire rt(32);
    Wire rs(32);
    Wire pc(30);
    Wire jta(26);
    Wire sysCallAddr(30);
    Wire BrType(1);
    Wire PCSrc(2);
    
    Wire incrPC(30);
    Wire nextPC(30);

    NextAddr nextAddr(&rt, &rs, &pc, &jta, &sysCallAddr,
                        &BrType, &PCSrc, incrPC, nextPC);

    rt.set(0);
    rs.set(0);
    pc.set(1);
    jta.set(0);
    sysCallAddr.set(23);
    BrType.set(0);
    PCSrc.set(3);

    nextAddr.eval();
    EXPECT_EQ(incrPC.getValue(), 2);
    EXPECT_EQ(nextPC.getValue(), 23);
}