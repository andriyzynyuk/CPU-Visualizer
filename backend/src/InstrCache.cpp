//
// TEMPORARY
//
#include "../include/InstrCache.hpp"

InstrCache::InstrCache(Wire* PC, Wire& INSTR)
    : pc(PC), instr(INSTR)
{}

void InstrCache::eval(){
    instr.set(instructions[pc->getValue()].raw);
}

void InstrCache::setInstructions(std::vector<Instruction> Instructions) {
    instructions = Instructions;
}

Instruction InstrCache::getCurrentInstruction() {
    return instructions[pc->getValue()];
}