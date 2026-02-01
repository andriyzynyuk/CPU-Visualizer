#pragma once

#include "Wire.hpp"
#include "NextAddr.hpp"
#include "PC.hpp"
#include "InstrCache.hpp"
#include "Instruction.hpp"
#include "ControlUnit.hpp"
#include "MUX.hpp"
#include "RegFile.hpp"
#include "SignExtender.hpp"
#include "ALU.hpp"

struct CPU {
    // Internal wires
    Wire IncrPC; //30 bits
    Wire NextPC; //30 bits
    Wire PC_out; //30 bits
    Wire Instr;
    Wire jta; //26 bits
    Wire rs; //5 bits
    Wire rt; //5 bits
    Wire rd; //5 bits
    Wire sh; //5 bits
    Wire returnAddress;
    Wire imm; //16 bits
    Wire imm_se;
    Wire op; //6 bits
    Wire fn; //6 bits
    Wire regDstIn; //5 bit
    Wire rs_out;
    Wire rt_out;
    Wire ALUSrcMux_out;
    Wire Ovfl; //1 bit
    Wire ALU_out;
    //Wire DataCache_out
    Wire RegIn;

    Wire muxFake; // for unused mux inputs

    Wire regWrite; //1 bit
    Wire regDst; //2 bits
    Wire regDst_s1; //1 bit
    Wire regDst_s0; //1 bit
    Wire regInSrc; //2 bits
    Wire regInSrc_s1; //1 bit
    Wire regInSrc_s0; //1 bit
    Wire ALUSrc; //1 bit
    Wire addSub; //1bit
    Wire constVar; //1 bit
    Wire logicFunc; //2 bits
    Wire funcClass; //2 bits
    Wire dataRead; //1 bit unused
    Wire dataWrite; //1 bit unused
    Wire BrType; //2 bit
    Wire PCSrc; //2 bit
    Wire SysCallAddr; //30 bits
    Wire shiftFunc; //2 bits

    // Gates
    NextAddr nextAddr;
    PC pc;
    InstrCache instrCache;
    ControlUnit controlUnit;
    MUX4to1 regDstMux;
    RegFile regFile;
    SignExtender signExtender;
    MUX2to1 ALUSrc_MUX;
    ALU alu;
    //DataCache
    MUX4to1 regInSrc_MUX;

    CPU();
    void loadInstructions(std::vector<Instruction> instructions);
    //void loadDataCache
    void firstCycle();
    void executeCycle();
    uint32_t getWireByPath(const std::string& path);
};