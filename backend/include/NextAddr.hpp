#pragma once

#include "Component.hpp"
#include "Wire.hpp"
#include "Gates.hpp"
#include "Adder.hpp"
#include "SignExtender.hpp"
#include "BranchCondCheck.hpp"
#include "MUX.hpp"

struct NextAddr : Component {
    // Inputs
    Wire *rt;
    Wire *rs;
    Wire *pc;
    Wire *jta;
    Wire *SysCallAddr;

    Wire *BrType;
    Wire *PCSrc;

    // Internal wires
    Wire rs30MSB;
    Wire BrTrue;
    Wire BrTrue_SE;
    Wire imm;
    Wire imm_SE;
    Wire bcc;
    Wire pc4MSB;
    Wire cin;
    Wire cout;
    Wire s0;
    Wire s1;
    Wire jtaPC4;

    // Output
    Wire &IncrPC;
    Wire &NextPC;

    // Gates
    BranchCondCheck bccModule;
    SignExtender seImm;
    SignExtender seBrTrue;
    AndGate andGate;
    Adder adder;
    MUX4to1 mux;

    NextAddr(Wire* RT, Wire* RS, Wire* PC, Wire* JTA, Wire* SYSCallAddr,
                    Wire* BRType, Wire* PCSRC,
                    Wire& INCRPC, Wire& NEXTPC);
    void eval() override;
    uint32_t getWireByPath(const std::string& path);
};