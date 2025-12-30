#include "../include/Gates.hpp"

AndGate::AndGate(const std::vector<Wire*>& in, Wire& out)
    : inputs(in), output(out) {}

void AndGate::eval() {
    uint32_t result = ~0u;
    for (auto w : inputs) {
        result &= w->getValue();
    }
    output.set(result);
}

OrGate::OrGate(const std::vector<Wire*>& in, Wire& out)
    : inputs(in), output(out) {}

void OrGate::eval() {
    uint32_t result = 0;
    for (auto w : inputs) {
        result |= w->getValue();
    }
    output.set(result);
}

XorGate::XorGate(const std::vector<Wire*>& in, Wire& out)
    : inputs(in), output(out) {}

void XorGate::eval(){
    uint32_t result = 0;
    for (auto w : inputs) {
        result ^= w->getValue();
    }
    output.set(result);
}