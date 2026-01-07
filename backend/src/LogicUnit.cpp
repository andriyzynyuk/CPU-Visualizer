#include "../include/LogicUnit.hpp"

LogicUnit::LogicUnit(Wire* X, Wire* Y, Wire* LogicFunc, Wire& Logic)
    : x(X), y(Y), logicFunction(LogicFunc), logic(Logic),

        ANDWire(32), ORWire(32), XORWire(32), NORWire(32), s0(1), s1(1),

        andGate({x, y}, ANDWire),
        orGate({x, y}, ORWire),
        xorGate({x, y}, XORWire),
        norGate({x, y}, NORWire),
        mux4to1(&ANDWire, &ORWire, &XORWire, &NORWire, &s1, &s0, logic)
{}

void LogicUnit::eval(){
    s0.set(logicFunction->getBit(0));
    s1.set(logicFunction->getBit(1));

    andGate.eval();
    orGate.eval();
    xorGate.eval();
    norGate.eval();
    mux4to1.eval();
}