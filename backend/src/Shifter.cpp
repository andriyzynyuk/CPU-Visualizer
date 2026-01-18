#include "../include/Shifter.hpp"

Shifter::Shifter(Wire* Y, Wire* Direction, Wire& S)
    : y(Y), direction(Direction), s(S)
{}

void Shifter::eval() {
    if (direction->getValue()) {
        s.set(y->getValue() << 1);
    } else {
        s.set(y->getValue() >> 1);
    }
}