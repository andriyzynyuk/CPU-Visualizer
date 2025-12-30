#pragma once

#include <vector>
#include "Wire.hpp"
#include "Component.hpp"

struct AndGate : Component {
    std::vector<Wire*> inputs;
    Wire& output;

    AndGate(const std::vector<Wire*>& in, Wire& out);
    void eval() override;
};

struct OrGate : Component {
    std::vector<Wire*> inputs;
    Wire& output;

    OrGate(const std::vector<Wire*>& in, Wire& out);
    void eval() override;
};

struct XorGate : Component {
    std::vector<Wire*> inputs;
    Wire& output;

    XorGate(const std::vector<Wire*>& in, Wire& out);
    void eval() override;
};