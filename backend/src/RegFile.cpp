//
// TEMPORARY
//
#include "../include/RegFile.hpp"

RegFile::RegFile(Wire* RS, Wire* RT, Wire* WriteData, Wire* RegIn, Wire* RegWrite,
                    Wire& RS_out, Wire& RT_out)
    : rs(RS), rt(RT), writeData(WriteData), regIn(RegIn), regWrite(RegWrite),
        rs_out(RS_out), rt_out(RT_out)
{
    for (int i = 0; i < 32; i++) {
        registers[i] = 0;
    }
}



void RegFile::eval(){
    rs_out.set(registers[rs->getValue()]);
    rt_out.set(registers[rt->getValue()]);

    if (regWrite->getValue()) {
        registers[writeData->getValue()] = regIn->getValue();
    }
}

uint32_t RegFile::getWireByPath(const std::string& path) {

    if (path.rfind("registers[", 0) == 0) {
        size_t endBracket = path.find(']');
        if (endBracket == std::string::npos) return -1;
        
        int index = std::stoi(path.substr(10, endBracket - 10));
        if (index < 0 || index >= 32) return -1;
        
        return registers[index];
    }

    return -1; // Wire not found
}