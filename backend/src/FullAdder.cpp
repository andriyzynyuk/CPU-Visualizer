#include "../include/FullAdder.hpp"

FullAdder::FullAdder(Wire* X, Wire* Y, Wire* C_IN, Wire& SUM, Wire& C_OUT)
    :x(X), y(Y), cin(C_IN),
        sum(SUM), cout(C_OUT),

        xor0(1), and0(1), and1(1),
        
        xorGate0({x, y}, xor0),
        andGate0({x, y}, and0),
        xorGate1({&xor0, cin}, sum),
        andGate1({&xor0, cin}, and1),
        orGate0({&and0, &and1}, cout)
{}



void FullAdder::eval(){
    xorGate0.eval();
    andGate0.eval();
    xorGate1.eval();
    andGate1.eval();
    orGate0.eval();
}