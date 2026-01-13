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