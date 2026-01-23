#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"
#include "Shifter.hpp"
#include "Adder.hpp"
#include "LogicUnit.hpp"
#include "SignExtender.hpp"

struct ALU : Component {
    // Inputs
    Wire* x;
    Wire* y;
    Wire* addSub;
    Wire* shiftDirection;
    Wire* logicFunc;
    Wire* funcClass;

    // Internal wires
    Wire yXOR;
    Wire shiftedY;
    Wire xPlusY;
    Wire logic;
    Wire xPlusYMsb;

    Wire AddSub_SE;

    Wire funcClass_s0;
    Wire funcClass_s1;

    // Output
    Wire &s;
    Wire &Cout;

    // Gates
    SignExtender se;
    XorGate xorGate;
    Shifter shifter;
    Adder adder;
    LogicUnit lu;
    MUX4to1 mux;
    


    ALU(Wire* X, Wire* Y, Wire* AddSub,
        Wire* ShiftDirection, Wire* LogicFunc, Wire* FuncClass,
        Wire& S, Wire& COUT);
    void eval() override;
    uint32_t getWireByPath(const std::string& path);
};
