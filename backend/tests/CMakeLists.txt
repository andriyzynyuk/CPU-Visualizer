include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(cpu_tests
    test_gates.cpp
    test_wire.cpp
    test_fullAdder.cpp
    test_adder.cpp
    test_shifter.cpp
    test_mux.cpp
    test_lu.cpp
    test_signextender.cpp
    test_alu.cpp
    test_branchCondCheck.cpp
    test_nextAddr.cpp
    test_regFile.cpp
)

target_link_libraries(cpu_tests
    cpu_sim
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cpu_tests)
