#pragma once

#include "Component.hpp"
#include "Wire.hpp"

struct SignExtender : Component {
    Wire* input;
    Wire& output;

    SignExtender(Wire* in, Wire& out);
    void eval() override;
};