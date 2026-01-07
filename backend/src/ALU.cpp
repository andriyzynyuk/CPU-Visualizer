#include "../include/ALU.hpp"

ALU::ALU(Wire* X, Wire* Y, Wire* AddSub,
        Wire* ShiftDirection, Wire* LogicFunc, Wire* FuncClass,
            Wire& S, Wire& COUT)

    : x(X), y(Y), addSub(AddSub), shiftDirection(ShiftDirection),
        logicFunc(LogicFunc), funcClass(FuncClass),
        s(S), Cout(COUT),

        yXOR(32), shiftedY(32), xPlusY(32), logic(32), xPlusYMsb(1),
        AddSub_SE(32), xPlusYMsb_SE(32), funcClass_s0(1), funcClass_s1(1),

        se(addSub, AddSub_SE),
        xorGate({y, &AddSub_SE}, yXOR),
        shifter(y, shiftDirection, shiftedY),
        adder(x, &yXOR, addSub, xPlusY, Cout),
        MSB_SE(&xPlusYMsb, xPlusYMsb_SE),
        lu(x, y, logicFunc, logic),
        mux(&shiftedY, &xPlusYMsb_SE, &xPlusY, &logic, &funcClass_s1, &funcClass_s0, s)
{}

void ALU::eval(){
    funcClass_s0.set(funcClass->getBit(0));
    funcClass_s1.set(funcClass->getBit(1));

    se.eval();
    xorGate.eval();
    shifter.eval();
    adder.eval();

    xPlusYMsb.set(xPlusY.getBit(31));
    
    MSB_SE.eval();
    lu.eval();
    mux.eval();
}