#pragma once

#include <vector>
#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"

struct Shifter : Component {
    // Inputs
    Wire* y;
    Wire* direction;

    // Internal wires
    std::vector<Wire> ANDGateOut;
    std::vector<Wire> ORGateOut;
    Wire directionNot;
    std::vector<Wire> y_bits, s_bits;

    // Output
    Wire &s;

    // Gates
    std::vector<AndGate*> andGate;
    std::vector<OrGate*> orGate;
    NotGate* notGate;

    Shifter(Wire* Y, Wire* Direction, Wire& S);
    ~Shifter();
    void eval() override;
};