#include "../include/MUX.hpp"

MUX4to1::MUX4to1(Wire* IN0, Wire* IN1, Wire* IN2, Wire* IN3,
                    Wire* S1, Wire* S0, Wire& OUT)

    : input0(IN0), input1(IN1), input2(IN2), input3(IN3), 
        s0(S0), s1(S1), out(OUT),

        ANDWire0(32), ANDWire1(32), ANDWire2(32), ANDWire3(32),
        s0n(1), s1n(1), s0_SE(32), s1_SE(32), s0n_SE(32), s1n_SE(32),

        se0(s0, s0_SE),
        se1(s1, s1_SE),
        notGateS0(s0, s0n),
        notGateS1(s1, s1n),
        seN0(&s0n, s0n_SE),
        seN1(&s1n, s1n_SE),
        andGate0({&s1n_SE, &s0n_SE, input0}, ANDWire0),
        andGate1({&s1n_SE, &s0_SE, input1}, ANDWire1),
        andGate2({&s1_SE, &s0n_SE, input2}, ANDWire2),
        andGate3({&s1_SE, &s0_SE, input3}, ANDWire3),
        orGate({&ANDWire0, &ANDWire1, &ANDWire2, &ANDWire3}, out)
{}

void MUX4to1::eval(){
    se0.eval();
    se1.eval();
    notGateS0.eval();
    notGateS1.eval();
    seN0.eval();
    seN1.eval();
    andGate0.eval();
    andGate1.eval();
    andGate2.eval();
    andGate3.eval();
    orGate.eval();
}

uint32_t MUX4to1::getWireByPath(const std::string& path) {
    // INPUTS
    if (path == "input0") return input0->getValue();
    if (path == "input1") return input1->getValue();
    if (path == "input2") return input2->getValue();
    if (path == "input3") return input3->getValue();
    if (path == "s0") return s0->getValue();
    if (path == "s1") return s1->getValue();
    
    // INTERNAL
    if (path == "s0n") return s0n.getValue();
    if (path == "s1n") return s1n.getValue();
    if (path == "ANDWire0") return ANDWire0.getValue();
    if (path == "ANDWire1") return ANDWire1.getValue();
    if (path == "ANDWire2") return ANDWire2.getValue();
    if (path == "ANDWire3") return ANDWire3.getValue();
    
    // OUTPUTS
    if (path == "out") return out.getValue();

    return -1;
}

MUX2to1::MUX2to1(Wire* IN0, Wire* IN1, Wire* S0, Wire& OUT)
    : input0(IN0), input1(IN1), s0(S0), out(OUT),
        s0n(1), s0n_SE(32), s0_SE(32), ANDWire0(32), ANDWire1(32),

        se0(s0, s0_SE),
        notGateS0(s0, s0n),
        seN0(&s0n, s0n_SE),
        andGate0({input0, &s0n_SE}, ANDWire0),
        andGate1({input1, &s0_SE}, ANDWire1),
        orGate({&ANDWire0, &ANDWire1}, out)
{}

void MUX2to1::eval(){
    se0.eval();
    notGateS0.eval();
    seN0.eval();
    andGate0.eval();
    andGate1.eval();
    orGate.eval();
}

uint32_t MUX2to1::getWireByPath(const std::string& path) {
    // INPUTS
    if (path == "input0") return input0->getValue();
    if (path == "input1") return input1->getValue();
    if (path == "s0") return s0->getValue();
    
    // INTERNAL
    if (path == "s0n") return s0n.getValue();
    if (path == "ANDWire0") return ANDWire0.getValue();
    if (path == "ANDWire1") return ANDWire1.getValue();
    
    // OUTPUTS
    if (path == "out") return out.getValue();

    return -1;
}