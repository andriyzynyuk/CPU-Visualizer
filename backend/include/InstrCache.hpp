//
// TEMPORARY
//

#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Instruction.hpp"

#include <vector>

struct InstrCache : Component {
    // Inputs
    Wire *pc; //30 bit

    // Output
    Wire &instr; //32 bit

    std::vector<Instruction> instructions;

    InstrCache(Wire* pc, Wire& instr);
    void eval() override;
    void setInstructions(std::vector<Instruction> Instructions);
    Instruction getCurrentInstruction();
};