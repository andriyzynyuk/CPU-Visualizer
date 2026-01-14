#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"
#include "Adder.hpp"
#include "MUX.hpp"

struct BranchCondCheck : Component {
    // Inputs
    Wire *rt;
    Wire *rs;
    Wire *BrType;

    // Internal wires
    Wire rsMSB;
    Wire rsNot;
    Wire cin;
    Wire cout;
    Wire adderResult;
    Wire ORAdderResult;
    Wire beq;
    Wire const0;
    Wire BrTypeMSB;
    Wire bltz;
    Wire s0;
    Wire s1;

    // Output
    Wire &BrTrue;

    // Gates
    NotGate reverseRs;
    Adder adder;
    NotGate notGate;
    AndGate andGate;
    MUX4to1 mux;

    BranchCondCheck(Wire* RT, Wire* RS, Wire* BRType, Wire& BRTrue);
    void eval() override;
};