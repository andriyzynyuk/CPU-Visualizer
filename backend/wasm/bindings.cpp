#include "../include/CPU.hpp"
#include "../include/Instruction.hpp"
#include <vector>
#include <cstdint>
#include <string>

extern "C" {
    CPU* cpu_create() {
        return new CPU();
    }

    void cpu_destroy(CPU* cpu) {
        delete cpu;
    }

    void cpu_first_cycle(CPU* cpu) {
        cpu->firstCycle();
    }

    void cpu_execute_cycle(CPU* cpu) {
        cpu->executeCycle();
    }
    void cpu_load_instruction(CPU* cpu, uint32_t instr) {
        cpu->loadInstructions({Instruction{instr}});
    }

    void cpu_load_instructions(CPU* cpu, const uint32_t* data, int count) {
        std::vector<Instruction> instructions;
        instructions.reserve(count);

        for (int i = 0; i < count; ++i) {
            Instruction instr;
            instr.raw = data[i];
            instructions.push_back(instr);
        }

        cpu->loadInstructions(instructions);
    }

    uint32_t cpu_get_wire_value(CPU* cpu, std::string wire) {
        return cpu->getWireByPath(wire);
    }

    // R Type Instructions
    uint32_t instr_ADD(uint8_t rd, uint8_t rs, uint8_t rt) {
        return Instruction::ADD(rd, rs, rt).raw;
    }

    uint32_t instr_SUB(uint8_t rd, uint8_t rs, uint8_t rt) {
        return Instruction::SUB(rd, rs, rt).raw;
    }

    uint32_t instr_SLT(uint8_t rd, uint8_t rs, uint8_t rt) {
        return Instruction::SLT(rd, rs, rt).raw;
    }

    uint32_t instr_AND(uint8_t rd, uint8_t rs, uint8_t rt) {
        return Instruction::AND(rd, rs, rt).raw;
    }

    uint32_t instr_OR(uint8_t rd, uint8_t rs, uint8_t rt) {
        return Instruction::OR(rd, rs, rt).raw;
    }

    uint32_t instr_XOR(uint8_t rd, uint8_t rs, uint8_t rt) {
        return Instruction::XOR(rd, rs, rt).raw;
    }

    uint32_t instr_NOR(uint8_t rd, uint8_t rs, uint8_t rt) {
        return Instruction::NOR(rd, rs, rt).raw;
    }

    uint32_t instr_JR(uint8_t rs) {
        return Instruction::JR(rs).raw;
    }

    // I Type Instructions
    uint32_t instr_ADDI(uint8_t rt, uint8_t rs, uint16_t imm) {
        return Instruction::ADDI(rt, rs, imm).raw;
    }

    uint32_t instr_SLTI(uint8_t rt, uint8_t rs, uint16_t imm) {
        return Instruction::SLTI(rt, rs, imm).raw;
    }

    uint32_t instr_ANDI(uint8_t rt, uint8_t rs, uint16_t imm) {
        return Instruction::ANDI(rt, rs, imm).raw;
    }

    uint32_t instr_ORI(uint8_t rt, uint8_t rs, uint16_t imm) {
        return Instruction::ORI(rt, rs, imm).raw;
    }

    uint32_t instr_XORI(uint8_t rt, uint8_t rs, uint16_t imm) {
        return Instruction::XORI(rt, rs, imm).raw;
    }

    uint32_t instr_BLTZ(uint8_t rs, uint16_t imm) {
        return Instruction::BLTZ(rs, imm).raw;
    }

    uint32_t instr_BEQ(uint8_t rt, uint8_t rs, uint16_t imm) {
        return Instruction::BEQ(rt, rs, imm).raw;
    }

    uint32_t instr_BNE(uint8_t rt, uint8_t rs, uint16_t imm) {
        return Instruction::BNE(rt, rs, imm).raw;
    }

    // === J-Type Instructions ===
    uint32_t instr_JUMP(uint32_t jta) {
        return Instruction::JUMP(jta).raw;
    }

    uint32_t instr_JAL(uint32_t jta) {
        return Instruction::JAL(jta).raw;
    }

}