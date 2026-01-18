//
// TEMPORARY
//

#pragma once

#include "Component.hpp"
#include "Wire.hpp"

struct RegFile : Component {
    // Inputs
    Wire *rs; //5 bit
    Wire *rt; //5 bit
    Wire *writeData; //5 bit
    Wire *regIn; //32 bit
    Wire *regWrite; //1 bit

    // Output
    Wire &rs_out; //32 bit
    Wire &rt_out; //32 bit

    int32_t registers[32];

    RegFile(Wire* RS, Wire* RT, Wire* WriteData, Wire* RegIn, Wire* RegWrite,
                    Wire& RS_out, Wire& RT_OUT);
    void eval() override;
    uint32_t getWireByPath(const std::string& path);
};