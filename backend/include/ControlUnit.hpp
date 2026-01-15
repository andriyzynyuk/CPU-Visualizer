//
// TEMPORARY
//

#pragma once

#include <cstdint>

#include "Component.hpp"
#include "Wire.hpp"

struct ControlUnit : Component {
    // Inputs
    Wire *op;
    Wire *fn;

    // Output
    Wire &regWrite;
    Wire &regDst;
    Wire &regInSrc;
    Wire &ALUSrc;
    Wire &addSub;
    Wire &logicFunc;
    Wire &funcClass;
    Wire &dataRead;
    Wire &dataWrite;
    Wire &BrType;
    Wire &PCSrc;

    ControlUnit(Wire* OP, Wire* FN, 
                Wire& RegWrite, Wire& RegDst, Wire& RegInSrc, Wire& ALUSRC,
                Wire& AddSub, Wire& LogicFunc, Wire& FuncClass, Wire& DataRead,
                Wire& DataWrite, Wire& BRType, Wire& PCSRC);
    void eval() override;
};