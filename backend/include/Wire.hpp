#pragma once

#include <cstdint>

struct Wire {
    uint32_t value = 0;
    uint8_t width;

    explicit Wire(uint8_t w) : width(w) {}

    void set(uint32_t v) {
        if (width >= 32)
            value = v;
        else
            value = v & ((1u << width) - 1);
    }

    uint32_t getValue() const {
        return value;
    }

    bool getBit(uint8_t i) const {
        return (value >> i) & 1u;
    }

    void setBit(uint8_t i, bool b) {
        if (i >= width) return;
        if (b) value |= (1u << i);
        else   value &= ~(1u << i);
    }
};