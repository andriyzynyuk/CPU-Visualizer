#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"
#include "SignExtender.hpp"

struct MUX4to1 : Component {
    // Inputs
    Wire* input0;
    Wire* input1;
    Wire* input2;
    Wire* input3;

    Wire* s0;
    Wire* s1;

    // Internal wires
    Wire s0n;
    Wire s1n;

    Wire s0_SE;
    Wire s1_SE;
    Wire s0n_SE;
    Wire s1n_SE;

    Wire ANDWire0;
    Wire ANDWire1;
    Wire ANDWire2;
    Wire ANDWire3;

    // Output
    Wire &out;

    // Gates
    SignExtender se0;
    SignExtender se1;
    SignExtender seN0;
    SignExtender seN1;
    NotGate notGateS0;
    NotGate notGateS1;
    AndGate andGate0;
    AndGate andGate1;
    AndGate andGate2;
    AndGate andGate3;
    OrGate orGate;

    MUX4to1(Wire* IN0, Wire* IN1, Wire* IN2, Wire* IN3,
            Wire* S1, Wire* S0, Wire& OUT);
    void eval() override;
    uint32_t getWireByPath(const std::string& path);
};

struct MUX2to1 : Component {
    // Inputs
    Wire* input0;
    Wire* input1;

    Wire* s0;

    // Internal wires
    Wire s0n;

    Wire s0_SE;
    Wire s0n_SE;

    Wire ANDWire0;
    Wire ANDWire1;

    // Output
    Wire &out;

    // Gates
    SignExtender se0;
    SignExtender seN0;
    NotGate notGateS0;
    AndGate andGate0;
    AndGate andGate1;
    OrGate orGate;

    MUX2to1(Wire* IN0, Wire* IN1,
            Wire* S0, Wire& OUT);
    void eval() override;
    uint32_t getWireByPath(const std::string& path);
};