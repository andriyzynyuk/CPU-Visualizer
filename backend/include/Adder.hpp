#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "FullAdder.hpp"

struct Adder : Component {
    // Inputs
    Wire *x;
    Wire *y;
    Wire *cin;

    // Internal wires
    std::vector<Wire> X_bits;
    std::vector<Wire> Y_bits;
    std::vector<Wire> sum_bits;
    std::vector<Wire> carries;

    // Output
    Wire &sum;
    Wire &cout;

    // Gates
    FullAdder* fullAdders[32];

    Adder(Wire* X, Wire* Y, Wire* C_IN, Wire& SUM, Wire& C_OUT);
    ~Adder();
    void eval() override;
    uint32_t getWireByPath(const std::string& path);
};