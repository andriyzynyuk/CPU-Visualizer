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

uint32_t CPU::getWireByPath(const std::string& path) {
    if (path.rfind("nextAddr.", 0) == 0) {
        return nextAddr.getWireByPath(path.substr(9));
    }
    if (path.rfind("regFile.", 0) == 0) {
        return regFile.getWireByPath(path.substr(8));
    }
    if (path.rfind("ALUSrc_MUX.", 0) == 0) {
        return ALUSrc_MUX.getWireByPath(path.substr(11));
    }
    if (path.rfind("alu.", 0) == 0) {
        return alu.getWireByPath(path.substr(4));
    }
    if (path.rfind("regInSrc_MUX.", 0) == 0) {
        return regInSrc_MUX.getWireByPath(path.substr(13));
    }
    
    // INTERNAL
    if (path == "IncrPC") return IncrPC.getValue();
    if (path == "NextPC") return NextPC.getValue();
    if (path == "PC_out") return PC_out.getValue();
    if (path == "Instr") return Instr.getValue();
    if (path == "jta") return jta.getValue();
    if (path == "rs") return rs.getValue();
    if (path == "rt") return rt.getValue();
    if (path == "rd") return rd.getValue();
    if (path == "returnAddress") return returnAddress.getValue();
    if (path == "imm") return imm.getValue();
    if (path == "imm_se") return imm_se.getValue();
    if (path == "op") return op.getValue();
    if (path == "fn") return fn.getValue();
    if (path == "regDstIn") return regDstIn.getValue();
    if (path == "rs_out") return rs_out.getValue();
    if (path == "rt_out") return rt_out.getValue();
    if (path == "ALUSrcMux_out") return ALUSrcMux_out.getValue();
    if (path == "Ovfl") return Ovfl.getValue();
    if (path == "ALU_out") return ALU_out.getValue();
    if (path == "RegIn") return RegIn.getValue();
    if (path == "regWrite") return regWrite.getValue();
    if (path == "regDst") return regDst.getValue();
    if (path == "regInSrc") return regInSrc.getValue();
    if (path == "ALUSrc") return ALUSrc.getValue();
    if (path == "addSub") return addSub.getValue();
    if (path == "logicFunc") return logicFunc.getValue();
    if (path == "funcClass") return funcClass.getValue();
    if (path == "dataRead") return dataRead.getValue();
    if (path == "dataWrite") return dataWrite.getValue();
    if (path == "BrType") return BrType.getValue();
    if (path == "PCSrc") return PCSrc.getValue();
    if (path == "SysCallAddr") return SysCallAddr.getValue();
    if (path == "shiftDirection") return shiftDirection.getValue();

    return -1;
}