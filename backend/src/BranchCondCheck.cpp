#include "../include/BranchCondCheck.hpp"

BranchCondCheck::BranchCondCheck(Wire* RT, Wire* RS, Wire* BRType, Wire& BRTrue)
    : rt(RT), rs(RS), BrType(BRType),
      BrTrue(BRTrue),

      rsMSB(1), rsNot(32), cin(1), cout(1), adderResult(32), ORAdderResult(1),
      beq(1), const0(1), BrTypeMSB(1), bltz(1), s0(1), s1(1),

      reverseRs(rs, rsNot),
      adder(rt, &rsNot, &cin, adderResult, cout),
      notGate(&ORAdderResult, beq),
      andGate({&rsMSB, &BrTypeMSB}, bltz),
      mux(&const0, &beq, &ORAdderResult, &bltz, &s1, &s0, BrTrue)
{}



void BranchCondCheck::eval(){
    rsMSB.set(rs->getBit(31));
    reverseRs.eval();
    cin.set(1);
    adder.eval();

    int adderOr = adderResult.getBit(0);
    for (int i = 1; i < 32; i++) {
        adderOr |= adderResult.getBit(i);
    }
    ORAdderResult.set(adderOr);

    notGate.eval();

    BrTypeMSB.set(BrType->getBit(1));
    andGate.eval();

    const0.set(0);
    s1.set(BrType->getBit(1));
    s0.set(BrType->getBit(0));
    mux.eval();
}

uint32_t BranchCondCheck::getWireByPath(const std::string& path) {
    if (path.rfind("mux.", 0) == 0) {
        return mux.getWireByPath(path.substr(4));
    }
    if (path.rfind("adder.", 0) == 0) {
        return adder.getWireByPath(path.substr(6));
    }

    // INPUTS
    if (path == "rt") return rt->getValue();
    if (path == "rs") return rs->getValue();
    if (path == "BrType") return BrType->getValue();
    
    // INTERNAL
    if (path == "rsMSB") return rsMSB.getValue();
    if (path == "rsNot") return rsNot.getValue();
    if (path == "cin") return cin.getValue();
    if (path == "adderResult") return adderResult.getValue();
    if (path == "ORAdderResult") return ORAdderResult.getValue();
    if (path == "beq") return beq.getValue();
    if (path == "const0") return const0.getValue();
    if (path == "BrTypeMSB") return BrTypeMSB.getValue();
    if (path == "bltz") return bltz.getValue();
    
    // OUTPUTS
    if (path == "BrTrue") return BrTrue.getValue();

    return -1;
}