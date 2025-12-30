#pragma once

struct Component {
    virtual void eval() = 0;
    virtual ~Component() = default;
};