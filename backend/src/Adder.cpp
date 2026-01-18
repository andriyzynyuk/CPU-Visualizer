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

uint32_t Adder::getWireByPath(const std::string& path) {
    if (path.rfind("fullAdders[", 0) == 0) {
        size_t endBracket = path.find(']');
        if (endBracket == std::string::npos) return -1;
        
        int index = std::stoi(path.substr(11, endBracket - 11));
        if (index < 0 || index >= 32) return -1;
        
        // Check if there's a sub-path after "]."
        if (path.length() > endBracket + 1 && path[endBracket + 1] == '.') {
            std::string subPath = path.substr(endBracket + 2);
            return fullAdders[index]->getWireByPath(subPath);
        }
        
        return -1;
    }

    if (path.rfind("X_bits[", 0) == 0) {
        size_t endBracket = path.find(']');
        if (endBracket == std::string::npos) return -1;
        
        int index = std::stoi(path.substr(7, endBracket - 7));
        if (index < 0 || index >= 32) return -1;
        
        return X_bits[index].getValue();
    }

    if (path.rfind("Y_bits[", 0) == 0) {
        size_t endBracket = path.find(']');
        if (endBracket == std::string::npos) return -1;
        
        int index = std::stoi(path.substr(7, endBracket - 7));
        if (index < 0 || index >= 32) return -1;
        
        return Y_bits[index].getValue();
    }

    if (path.rfind("sum_bits[", 0) == 0) {
        size_t endBracket = path.find(']');
        if (endBracket == std::string::npos) return -1;
        
        int index = std::stoi(path.substr(9, endBracket - 9));
        if (index < 0 || index >= 32) return -1;
        
        return sum_bits[index].getValue();
    }

    if (path.rfind("carries[", 0) == 0) {
        size_t endBracket = path.find(']');
        if (endBracket == std::string::npos) return -1;
        
        int index = std::stoi(path.substr(8, endBracket - 8));
        if (index < 0 || index >= (int)carries.size()) return -1;
        
        return carries[index].getValue();
    }

    if (path == "cin") return cin->getValue();
    if (path == "cout") return cout.getValue();

    return -1; // Wire not found
}