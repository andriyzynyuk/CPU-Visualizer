#pragma once

#include <string>

struct Component {
    virtual void eval() = 0;
    virtual ~Component() = default;
    //virtual uint32_t getWireByPath(const std::string& path) {
    //    return -1;
    //}
};