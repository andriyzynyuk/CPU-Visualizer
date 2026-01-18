#include "../include/NextAddr.hpp"

NextAddr::NextAddr(Wire* RT, Wire* RS, Wire* PC, Wire* JTA, Wire* SYSCallAddr,
                    Wire* BRType, Wire* PCSRC,
                    Wire& INCRPC, Wire& NEXTPC)
    : rt(RT), rs(RS), pc(PC), jta(JTA), SysCallAddr(SYSCallAddr),
        BrType(BRType), PCSrc(PCSRC), IncrPC(INCRPC), NextPC(NEXTPC),

      rs30MSB(30), BrTrue(1), BrTrue_SE(30), imm(16), imm_SE(30),
        bcc(30), pc4MSB(4), cin(1), cout(1), s0(1), s1(1), jtaPC4(30),

      bccModule(rt, rs, BrType, BrTrue),
      seImm(&imm, imm_SE),
      seBrTrue(&BrTrue, BrTrue_SE),
      andGate({&imm_SE, &BrTrue_SE}, bcc),
      adder(&bcc, pc, &cin, IncrPC, cout),
      mux(&IncrPC, &jtaPC4, &rs30MSB, SysCallAddr, &s1, &s0, NextPC)
      
{}



void NextAddr::eval(){
    for (int i = 0; i < 30; i++) {
        rs30MSB.setBit(i, rs->getBit(i+2));
    }

    bccModule.eval();

    for (int i = 0; i < 16; i++) {
        imm.setBit(i, jta->getBit(i));
    }

    seImm.eval();
    seBrTrue.eval();
    andGate.eval();

    cin.set(1);

    adder.eval();

    for (int i = 0; i < 26; i++) {
        jtaPC4.setBit(i, jta->getBit(i));
    }
    jtaPC4.setBit(26, pc->getBit(26));
    jtaPC4.setBit(27, pc->getBit(27));
    jtaPC4.setBit(28, pc->getBit(28));
    jtaPC4.setBit(29, pc->getBit(29));

    s1.set(PCSrc->getBit(1));
    s0.set(PCSrc->getBit(0));

    mux.eval();
}

uint32_t NextAddr::getWireByPath(const std::string& path) {
    if (path.rfind("bccModule.", 0) == 0) {
        return bccModule.getWireByPath(path.substr(10));
    }
    if (path.rfind("adder.", 0) == 0) {
        return adder.getWireByPath(path.substr(6));
    }
    if (path.rfind("mux.", 0) == 0) {
        return mux.getWireByPath(path.substr(4));
    }

    // INPUTS
    if (path == "rt") return rt->getValue();
    if (path == "rs") return rs->getValue();
    if (path == "pc") return pc->getValue();
    if (path == "jta") return jta->getValue();
    if (path == "SysCallAddr") return SysCallAddr->getValue();
    if (path == "BrType") return BrType->getValue();
    if (path == "PCSrc") return PCSrc->getValue();
    
    // INTERNAL
    if (path == "rs30MSB") return rs30MSB.getValue();
    if (path == "BrTrue") return BrTrue.getValue();
    if (path == "imm") return imm.getValue();
    if (path == "imm_SE") return imm_SE.getValue();
    if (path == "bcc") return bcc.getValue();
    if (path == "pc4MSB") return pc4MSB.getValue();
    if (path == "cin") return cin.getValue();
    if (path == "jtaPC4") return jtaPC4.getValue();
    
    // OUTPUTS
    if (path == "IncrPC") return IncrPC.getValue();
    if (path == "NextPC") return NextPC.getValue();

    return -1;
}