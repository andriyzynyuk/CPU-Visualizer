#include "../include/CPU.hpp"

CPU::CPU()

    : IncrPC(30), NextPC(30), PC_out(30), Instr(32), jta(26),
        rs(5), rt(5), rd(5), returnAddress(32), imm(16), imm_se(32), op(6), fn(6), regDstIn(5),
        rs_out(32), rt_out(32), ALUSrcMux_out(32), Ovfl(1), ALU_out(32), RegIn(32), muxFake(32),
        regWrite(1), regDst(2), regInSrc(2), ALUSrc(1), addSub(1), logicFunc(2), funcClass(2),
        dataRead(1), dataWrite(1), BrType(2), PCSrc(2), SysCallAddr(30), shiftDirection(1),
        regDst_s1(1), regDst_s0(1), regInSrc_s1(1), regInSrc_s0(1),

        pc(&NextPC, PC_out),
        instrCache(&PC_out, Instr),
        controlUnit(&op, &fn,
                    regWrite, regDst, regInSrc, ALUSrc,
                    addSub, logicFunc, funcClass, dataRead,
                    dataWrite, BrType, PCSrc),
        regDstMux(&rt, &rd, &returnAddress, &muxFake,
                    &regDst_s1, &regDst_s0, regDstIn),
        regFile(&rs, &rt, &regDstIn, &RegIn, &regWrite,
                rs_out, rt_out),
        nextAddr(&rt_out, &rs_out, &PC_out, &jta, &SysCallAddr,
                    &BrType, &PCSrc,
                    IncrPC, NextPC),
        signExtender(&imm, imm_se),
        ALUSrc_MUX(&rt_out, &imm_se, &ALUSrc, ALUSrcMux_out),
        alu(&rs_out, &ALUSrcMux_out, &addSub,
            &shiftDirection, &logicFunc,
            &funcClass, ALU_out, Ovfl),
        regInSrc_MUX(&muxFake, &ALU_out, &IncrPC, &muxFake,
                    &regInSrc_s1, &regInSrc_s0, RegIn)
{}

void CPU::loadInstructions(std::vector<Instruction> instructions) {
    instrCache.setInstructions(instructions);
}

void CPU::firstCycle() {
    NextPC.set(0);
    pc.eval();
    instrCache.eval();

    op.set(instrCache.getCurrentInstruction().op());
    fn.set(instrCache.getCurrentInstruction().fn());
    controlUnit.eval();

    rt.set(instrCache.getCurrentInstruction().rt());
    rd.set(instrCache.getCurrentInstruction().rd());
    returnAddress.set(31);
    muxFake.set(0);
    regDst_s1.set(regDst.getBit(1));
    regDst_s0.set(regDst.getBit(0));
    regDstMux.eval();

    rs.set(instrCache.getCurrentInstruction().rs());
    regFile.eval();

    jta.set(instrCache.getCurrentInstruction().jta());
    SysCallAddr.set(0);
    nextAddr.eval();

    imm.set(instrCache.getCurrentInstruction().imm());
    signExtender.eval();

    ALUSrc_MUX.eval();

    shiftDirection.set(0);
    alu.eval();

    regInSrc_s1.set(regInSrc.getBit(1));
    regInSrc_s0.set(regInSrc.getBit(0));
    regInSrc_MUX.eval();

    regFile.eval();
}

void CPU::executeCycle() {
    pc.eval();
    instrCache.eval();

    op.set(instrCache.getCurrentInstruction().op());
    fn.set(instrCache.getCurrentInstruction().fn());
    controlUnit.eval();

    rt.set(instrCache.getCurrentInstruction().rt());
    rd.set(instrCache.getCurrentInstruction().rd());
    returnAddress.set(31);
    muxFake.set(0);
    regDst_s1.set(regDst.getBit(1));
    regDst_s0.set(regDst.getBit(0));
    regDstMux.eval();

    rs.set(instrCache.getCurrentInstruction().rs());
    regFile.eval();

    jta.set(instrCache.getCurrentInstruction().jta());
    SysCallAddr.set(0);
    nextAddr.eval();

    imm.set(instrCache.getCurrentInstruction().imm());
    signExtender.eval();

    ALUSrc_MUX.eval();

    shiftDirection.set(0);
    alu.eval();

    regInSrc_s1.set(regInSrc.getBit(1));
    regInSrc_s0.set(regInSrc.getBit(0));
    regInSrc_MUX.eval();

    regFile.eval();
}