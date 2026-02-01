#include "../include/ControlUnit.hpp"

ControlUnit::ControlUnit(Wire* OP, Wire* FN, 
                    Wire& RegWrite, Wire& RegDst, Wire& RegInSrc, Wire& ALUSRC,
                    Wire& AddSub, Wire& ConstVar, Wire& ShiftFunc, Wire& LogicFunc,
                    Wire& FuncClass, Wire& DataRead, Wire& DataWrite, Wire& BRType,
                    Wire& PCSRC)
    : op(OP), fn(FN), regWrite(RegWrite), regDst(RegDst), regInSrc(RegInSrc), ALUSrc(ALUSRC),
        addSub(AddSub), constVar(ConstVar), shiftFunc(ShiftFunc), logicFunc(LogicFunc),
        funcClass(FuncClass),dataRead(DataRead), dataWrite(DataWrite), BrType(BRType), PCSrc(PCSRC)
{}



void ControlUnit::eval(){
    int8_t OPcode = op->getValue();
    int8_t FNcode = fn->getValue();
    if(OPcode) {
        switch(OPcode) {
            //ADDI
            case 0b001000:
                regWrite.set(0b1);
                regDst.set(0b00);
                regInSrc.set(0b01);
                ALUSrc.set(0b1);
                addSub.set(0b0);

                funcClass.set(0b10);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SLTI
            case 0b001010:
                regWrite.set(0b1);
                regDst.set(0b00);
                regInSrc.set(0b01);
                ALUSrc.set(0b1);
                addSub.set(0b1);

                funcClass.set(0b01);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //ANDI
            case 0b001100:
                regWrite.set(0b1);
                regDst.set(0b00);
                regInSrc.set(0b01);
                ALUSrc.set(0b1);

                logicFunc.set(0b00);
                funcClass.set(0b11);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //ORI
            case 0b001101:
                regWrite.set(0b1);
                regDst.set(0b00);
                regInSrc.set(0b01);
                ALUSrc.set(0b1);

                logicFunc.set(0b01);
                funcClass.set(0b11);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //XORI
            case 0b001110:
                regWrite.set(0b1);
                regDst.set(0b00);
                regInSrc.set(0b01);
                ALUSrc.set(0b1);

                logicFunc.set(0b10);
                funcClass.set(0b11);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //JUMP
            case 0b000010:
                regWrite.set(0b0);

                dataRead.set(0b0);
                dataWrite.set(0b0);

                PCSrc.set(0b01);
                break;
            //BLTZ
            case 0b000001:
                regWrite.set(0b0);

                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b11);
                PCSrc.set(0b00);
                break;
            //BEQ
            case 0b000100:
                regWrite.set(0b0);

                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b01);
                PCSrc.set(0b00);
                break;
            //BNE
            case 0b000101:
                regWrite.set(0b0);

                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b10);
                PCSrc.set(0b00);
                break;
            //JAL
            case 0b000011:
                regWrite.set(0b1);
                regDst.set(0b10);
                regInSrc.set(0b10);

                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b01);
                break;
        }
    } else {
        switch (FNcode) {
            //ADD
            case 0b100000:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                addSub.set(0b0);

                funcClass.set(0b10);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SUB
            case 0b100010:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                addSub.set(0b1);

                funcClass.set(0b10);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SLT
            case 0b101010:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                addSub.set(0b1);

                funcClass.set(0b01);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //AND
            case 0b100100:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);

                logicFunc.set(0b00);
                funcClass.set(0b11);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //OR
            case 0b100101:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);

                logicFunc.set(0b01);
                funcClass.set(0b11);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //XOR
            case 0b100110:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);

                logicFunc.set(0b10);
                funcClass.set(0b11);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //NOR
            case 0b100111:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);

                logicFunc.set(0b11);
                funcClass.set(0b11);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //JR
            case 0b001000:
                regWrite.set(0b0);

                dataRead.set(0b0);
                dataWrite.set(0b0);

                PCSrc.set(0b10);
                break;
            //SLL
            case 0b000000:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                constVar.set(0b0);
                shiftFunc.set(0b01);

                funcClass.set(0b00);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SRL
            case 0b000010:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                constVar.set(0b0);
                shiftFunc.set(0b10);

                funcClass.set(0b00);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SRA
            case 0b000011:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                constVar.set(0b0);
                shiftFunc.set(0b11);

                funcClass.set(0b00);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SLLV
            case 0b000100:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                constVar.set(0b1);
                shiftFunc.set(0b01);

                funcClass.set(0b00);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SRLV
            case 0b000110:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                constVar.set(0b1);
                shiftFunc.set(0b10);

                funcClass.set(0b00);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
            //SRAV
            case 0b000111:
                regWrite.set(0b1);
                regDst.set(0b01);
                regInSrc.set(0b01);
                ALUSrc.set(0b0);
                constVar.set(0b1);
                shiftFunc.set(0b11);

                funcClass.set(0b00);
                dataRead.set(0b0);
                dataWrite.set(0b0);
                BrType.set(0b00);
                PCSrc.set(0b00);
                break;
        }
    }
}

//template
// regWrite.set(0b1);
// regDst.set(0b00);
// regInSrc.set(0b01);
// ALUSrc.set(0b1);
// constVar.set(0b1);
// shiftFunc.set(0b11);
// addSub.set(0b0);
// logicFunc.set(0b00);
// funcClass.set(0b10);
// dataRead.set(0b0);
// dataWrite.set(0b0);
// BrType.set(0b00);
// PCSrc.set(0b00);

//TODO:
//lw, sw
//syscall?