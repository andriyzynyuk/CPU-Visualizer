#include "../include/Shifter.hpp"

Shifter::Shifter(Wire* Y, Wire* Direction, Wire& S)
    : y(Y), direction(Direction), s(S), directionNot(1)
{
    ANDGateOut.resize(62, Wire(1));
    ORGateOut.resize(30, Wire(1));
    y_bits.resize(32, Wire(1));
    s_bits.resize(32, Wire(1));

    andGate.resize(62);
    orGate.resize(30);

    notGate = new NotGate(direction, directionNot);

    for (int i = 0; i < 32; i++) {
        y_bits[i].set(y->getBit(i));
    }

    for (int i = 1; i <= 30; i++) {
        int idx = 2 * (i - 1);
        andGate[idx] = new AndGate({&y_bits[i-1], direction}, ANDGateOut[idx]);
        andGate[idx + 1] = new AndGate({&y_bits[i+1], &directionNot}, ANDGateOut[idx + 1]);
        orGate[i - 1] = new OrGate({&ANDGateOut[idx], &ANDGateOut[idx + 1]}, s_bits[i]);
    }

    andGate[60] = new AndGate({&y_bits[1], &directionNot}, ANDGateOut[60]);

    andGate[61] = new AndGate({&y_bits[30], direction}, ANDGateOut[61]);
}

Shifter::~Shifter() {
    delete notGate;
    for (auto* gate : andGate) delete gate;
    for (auto* gate : orGate) delete gate;
}

void Shifter::eval() {
    for (int i = 0; i < 32; i++) {
        y_bits[i].set(y->getBit(i));
    }

    notGate->eval();

    for (auto* gate : andGate) {
        gate->eval();
    }

    s_bits[0].set(ANDGateOut[60].getValue());
    s_bits[31].set(ANDGateOut[61].getValue());

    for (auto* gate : orGate) {
        gate->eval();
    }

    for (int i = 0; i < 32; i++) {
        s.setBit(i, s_bits[i].getValue());
    }
}