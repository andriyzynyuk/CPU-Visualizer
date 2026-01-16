//
// TEMPORARY
//
#include "../include/PC.hpp"

PC::PC(Wire* PC_IN, Wire& PC_OUT)
    : pc_in(PC_IN), pc_out(PC_OUT)
{
    reg = 0;
}

void PC::eval(){
    reg = pc_in->getValue();
    pc_out.set(reg);
}