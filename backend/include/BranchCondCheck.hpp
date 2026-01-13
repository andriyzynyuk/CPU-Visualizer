#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"
#include "Adder.hpp"

struct BranchCondCheck : Component {
    // Inputs
    Wire *rt;
    Wire *rs;
    Wire *BrType;

    // Internal wires
    Wire rsNot;
    Wire adderResult;
    Wire cin;
    Wire cout;
    Wire ORAdderResult;
    Wire xorWire;

    // Output
    Wire &BrTrue;

    // Gates
    NotGate reverseRs;
    Adder adder;
    XorGate xorGate;
    NotGate notGate;

    BranchCondCheck(Wire* RT, Wire* RS, Wire* BRType, Wire& BRTrue);
    void eval() override;
};