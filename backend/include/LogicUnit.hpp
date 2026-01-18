#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"
#include "MUX.hpp"

struct LogicUnit : Component {
    // Inputs
    Wire* x;
    Wire* y;
    Wire* logicFunction;

    // Internal wires
    Wire ANDWire;
    Wire ORWire;
    Wire XORWire;
    Wire NORWire;
    Wire s0;
    Wire s1;

    // Output
    Wire &logic;

    // Gates
    AndGate andGate;
    OrGate orGate;
    XorGate xorGate;
    NorGate norGate;
    MUX4to1 mux4to1;

    LogicUnit(Wire* x, Wire* y, Wire* logicFunction, Wire& logic);
    void eval() override;
    uint32_t getWireByPath(const std::string& path);
};
