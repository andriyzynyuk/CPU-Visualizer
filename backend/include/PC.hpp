//
// TEMPORARY
//

#pragma once

#include "Component.hpp"
#include "Wire.hpp"

struct PC : Component {
    // Inputs
    Wire *pc_in;

    // Output
    Wire &pc_out;

    int32_t reg;

    PC(Wire* PC_IN, Wire& PC_OUT);
    void eval() override;
    //uint32_t getWireByPath(const std::string& path);
};