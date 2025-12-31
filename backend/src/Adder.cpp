#include "../include/Adder.hpp"

Adder::Adder(Wire* X, Wire* Y, Wire* C_IN, Wire& SUM, Wire& C_OUT)
    : x(X), y(Y), cin(C_IN), sum(SUM), cout(C_OUT),
      X_bits(32, Wire(1)), Y_bits(32, Wire(1)), sum_bits(32, Wire(1)), carries(33, Wire(1))
{
    for (int i = 0; i < 32; i++) {
        X_bits[i].set(x->getBit(i));
        Y_bits[i].set(y->getBit(i));
    }
    carries[0].set(cin->getValue() & 1);

    for (int i = 0; i < 32; i++) {
        fullAdders[i] = new FullAdder(&X_bits[i], &Y_bits[i], &carries[i], sum_bits[i], carries[i+1]);
    }
}

Adder::~Adder() {
    for (int i = 0; i < 32; i++) {
        delete fullAdders[i];
    }
}

void Adder::eval() {
    for (int i = 0; i < 32; i++) {
        X_bits[i].set(x->getBit(i));
        Y_bits[i].set(y->getBit(i));
    }
    carries[0].set(cin->getValue() & 1);

    for (int i = 0; i < 32; i++) {
        fullAdders[i]->eval();
        sum.setBit(i, sum_bits[i].getValue());
    }
    cout.set(carries[32].getValue() & 1);
}