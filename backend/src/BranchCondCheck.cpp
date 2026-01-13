#include "../include/BranchCondCheck.hpp"

BranchCondCheck::BranchCondCheck(Wire* RT, Wire* RS, Wire* BRType, Wire& BRTrue)
    : rt(RT), rs(RS), BrType(BRType),
      BrTrue(BRTrue),

      rsNot(32), adderResult(32), cin(1), cout(1), ORAdderResult(1), xorWire(1),

      reverseRs(rs, rsNot),
      adder(rt, &rsNot, &cin, adderResult, cout),
      xorGate({&ORAdderResult, BrType}, xorWire),
      notGate(&xorWire, BrTrue)
{}



void BranchCondCheck::eval(){
    reverseRs.eval();
    cin.set(1);
    adder.eval();

    int adderOr = adderResult.getBit(0);
    for (int i = 1; i < 32; i++) {
        adderOr |= adderResult.getBit(i);
    }
    ORAdderResult.set(adderOr);

    xorGate.eval();
    notGate.eval();
}