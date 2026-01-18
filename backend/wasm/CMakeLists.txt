cmake_minimum_required(VERSION 3.20)
project(cpu_wasm)

set(CMAKE_CXX_STANDARD 17)

add_library(cpu_core STATIC
    ../src/ALU.cpp
    ../src/Adder.cpp
    ../src/BranchCondCheck.cpp
    ../src/CPU.cpp
    ../src/ControlUnit.cpp
    ../src/FullAdder.cpp
    ../src/Gates.cpp
    ../src/InstrCache.cpp
    ../src/Instruction.cpp
    ../src/LogicUnit.cpp
    ../src/MUX.cpp
    ../src/NextAddr.cpp
    ../src/PC.cpp
    ../src/RegFile.cpp
    ../src/Shifter.cpp
    ../src/SignExtender.cpp
)

target_include_directories(cpu_core PRIVATE ../include)

add_executable(cpu bindings.cpp)

target_link_libraries(cpu PRIVATE cpu_core)

target_link_options(cpu PRIVATE
    -sWASM=1
    -sMODULARIZE=1
    -sEXPORT_NAME=CPUWasm
    -sEXPORTED_FUNCTIONS=_cpu_create,_cpu_destroy,_cpu_first_cycle,_cpu_execute_cycle,_cpu_load_instruction,_cpu_get_wire_value,_instr_ADD,_instr_SUB,_instr_SLT,_instr_ADDI,_instr_SLTI,_instr_AND,_instr_OR,_instr_XOR,_instr_NOR,_instr_ANDI,_instr_ORI,_instr_XORI,_instr_JUMP,_instr_JR,_instr_BLTZ,_instr_BEQ,_instr_BNE,_instr_JAL
    -sEXPORTED_RUNTIME_METHODS=cwrap,ccall,HEAPU8
)

set_target_properties(cpu PROPERTIES OUTPUT_NAME "cpu")