#include "../include/SignExtender.hpp"

SignExtender::SignExtender(Wire* in, Wire& out)
    : input(in), output(out) {}

void SignExtender::eval() {
    bool signBit = input->getBit(input->width - 1);
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        if (i < input->width) {
            if (input->getBit(i)) result |= (1u << i);
        } else {
            if (signBit) result |= (1u << i);
        }
    }
    output.set(result);
}