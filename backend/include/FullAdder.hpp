#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"

struct FullAdder : Component {
    // Inputs
    Wire *x;
    Wire *y;
    Wire *cin;

    // Internal wires
    Wire xor0;
    Wire and0;
    Wire and1;

    // Output
    Wire &sum;
    Wire &cout;

    // Gates
    XorGate xorGate0;
    AndGate andGate0;
    XorGate xorGate1;
    AndGate andGate1;
    OrGate  orGate0;

    FullAdder(Wire* X, Wire* Y, Wire* C_IN, Wire& SUM, Wire& C_OUT);
    void eval() override;
};