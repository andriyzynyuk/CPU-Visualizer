cmake_minimum_required(VERSION 3.20)
project(cpu_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(cpu_sim
    src/Gates.cpp
    src/FullAdder.cpp
    src/Adder.cpp
    src/Shifter.cpp
    src/MUX.cpp
    src/LogicUnit.cpp
    src/SignExtender.cpp
    src/ALU.cpp
    src/BranchCondCheck.cpp
    src/NextAddr.cpp
    src/RegFile.cpp
    src/Instruction.cpp
    src/InstrCache.cpp
    src/ControlUnit.cpp
)

target_include_directories(cpu_sim PUBLIC include)

add_executable(cpu_main 
    src/main.cpp
)
target_link_libraries(cpu_main cpu_sim)

enable_testing()
add_subdirectory(tests)