#pragma once

#include <vector>
#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"

struct Shifter : Component {
    // Inputs
    Wire* y;
    Wire* direction;

    // Output
    Wire &s;

    Shifter(Wire* Y, Wire* Direction, Wire& S);
    void eval() override;
    //uint32_t getWireByPath(const std::string& path);
};