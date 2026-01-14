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