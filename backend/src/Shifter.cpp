#include "../include/Shifter.hpp"

Shifter::Shifter(Wire* Y, Wire* Amount, Wire* Func, Wire& S)
    : y(Y), amount(Amount), func(Func), s(S)
{}

void Shifter::eval() {
    uint8_t shift = amount->getValue();

    if (func->getValue() == 0b00) {
        s.set(y->getValue());
    } else if (func->getValue() == 0b01) { // left logical
        s.set(y->getValue() << shift);
    } else if (func->getValue() == 0b10) { // right logical
        s.set(y->getValue() >> shift);
    } else if (func->getValue() == 0b11) { // right arithmetic
        int32_t val = static_cast<int32_t>(y->getValue()); // Making sure it's arithmetic shifting
        s.set(static_cast<uint32_t>(val >> shift)); // Back to unsigned
    }
}