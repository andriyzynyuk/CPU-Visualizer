#include <iostream>

#include "../include/Wire.hpp"
#include "../include/Adder.hpp"

int main() {
    Wire X(32);
    Wire Y(32);
    Wire C_IN(1);
    Wire SUM(32);
    Wire C_OUT(1);

    X.set(100);
    Y.set(100);
    C_IN.set(0);

    Adder adder(&X, &Y, &C_IN, SUM, C_OUT);
    adder.eval();

    std::cout << "X:" << X.getValue() << " Y:" << Y.getValue() << " c_in: " << C_IN.getValue() << std::endl;
    std::cout << "Sum: " << SUM.getValue() << " C_out: " << C_OUT.getValue() << std::endl;

    return 0;
}