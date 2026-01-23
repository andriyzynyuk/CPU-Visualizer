#include "../include/ALU.hpp"

ALU::ALU(Wire* X, Wire* Y, Wire* AddSub,
        Wire* ShiftDirection, Wire* LogicFunc, Wire* FuncClass,
            Wire& S, Wire& COUT)

    : x(X), y(Y), addSub(AddSub), shiftDirection(ShiftDirection),
        logicFunc(LogicFunc), funcClass(FuncClass),
        s(S), Cout(COUT),

        yXOR(32), shiftedY(32), xPlusY(32), logic(32), xPlusYMsb(1),
        AddSub_SE(32), funcClass_s0(1), funcClass_s1(1),

        se(addSub, AddSub_SE),
        xorGate({y, &AddSub_SE}, yXOR),
        shifter(y, shiftDirection, shiftedY),
        adder(x, &yXOR, addSub, xPlusY, Cout),
        lu(x, y, logicFunc, logic),
        mux(&shiftedY, &xPlusYMsb, &xPlusY, &logic, &funcClass_s1, &funcClass_s0, s)
{}

void ALU::eval(){
    funcClass_s0.set(funcClass->getBit(0));
    funcClass_s1.set(funcClass->getBit(1));

    se.eval();
    xorGate.eval();
    shifter.eval();
    adder.eval();

    xPlusYMsb.set(xPlusY.getBit(31));
    
    lu.eval();
    mux.eval();
}

uint32_t ALU::getWireByPath(const std::string& path) {
    // if (path.rfind("shifter.", 0) == 0) {
    //     return shifter.getWireByPath(path.substr(8));
    // }
    if (path.rfind("adder.", 0) == 0) {
        return adder.getWireByPath(path.substr(6));
    }
    if (path.rfind("lu.", 0) == 0) {
        return lu.getWireByPath(path.substr(3));
    }
    if (path.rfind("mux.", 0) == 0) {
        return mux.getWireByPath(path.substr(4));
    }

    // INPUTS
    if (path == "x") return x->getValue();
    if (path == "y") return y->getValue();
    if (path == "addSub") return addSub->getValue();
    if (path == "shiftDirection") return shiftDirection->getValue();
    if (path == "logicFunc") return logicFunc->getValue();
    if (path == "funcClass") return funcClass->getValue();
    
    // INTERNAL
    if (path == "yXOR") return yXOR.getValue();
    if (path == "shiftedY") return shiftedY.getValue();
    if (path == "xPlusY") return xPlusY.getValue();
    if (path == "logic") return logic.getValue();
    if (path == "xPlusYMsb") return xPlusYMsb.getValue();
    
    // OUTPUTS
    if (path == "s") return s.getValue();
    if (path == "Cout") return Cout.getValue();

    return -1;
}