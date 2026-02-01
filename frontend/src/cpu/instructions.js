import { getCpuApi } from './cpuApi';

let cached = null;
async function m() {
  if (cached) return cached;
  const a = await getCpuApi();
  const cwrap = a.module.cwrap.bind(a.module);

  // R-Type
  const instr_ADD = cwrap('instr_ADD', 'number', ['number','number','number']);
  const instr_SUB = cwrap('instr_SUB', 'number', ['number','number','number']);
  const instr_SLT = cwrap('instr_SLT', 'number', ['number','number','number']);
  const instr_AND = cwrap('instr_AND', 'number', ['number','number','number']);
  const instr_OR  = cwrap('instr_OR',  'number', ['number','number','number']);
  const instr_XOR = cwrap('instr_XOR', 'number', ['number','number','number']);
  const instr_NOR = cwrap('instr_NOR', 'number', ['number','number','number']);
  const instr_JR  = cwrap('instr_JR',  'number', ['number']);

  // I-Type
  const instr_ADDI = cwrap('instr_ADDI', 'number', ['number','number','number']);
  const instr_SLTI = cwrap('instr_SLTI', 'number', ['number','number','number']);
  const instr_ANDI = cwrap('instr_ANDI', 'number', ['number','number','number']);
  const instr_ORI  = cwrap('instr_ORI',  'number', ['number','number','number']);
  const instr_XORI = cwrap('instr_XORI', 'number', ['number','number','number']);
  const instr_BLTZ = cwrap('instr_BLTZ', 'number', ['number','number']);
  const instr_BEQ  = cwrap('instr_BEQ',  'number', ['number','number','number']);
  const instr_BNE  = cwrap('instr_BNE',  'number', ['number','number','number']);

  // J-Type
  const instr_JUMP = cwrap('instr_JUMP', 'number', ['number']);
  const instr_JAL  = cwrap('instr_JAL',  'number', ['number']);

  // Shift Instructions
  const instr_SLL  = cwrap('instr_SLL',  'number', ['number','number','number']);
  const instr_SRL  = cwrap('instr_SRL',  'number', ['number','number','number']);
  const instr_SRA  = cwrap('instr_SRA',  'number', ['number','number','number']);
  const instr_SLLV = cwrap('instr_SLLV', 'number', ['number','number','number']);
  const instr_SRLV = cwrap('instr_SRLV', 'number', ['number','number','number']);
  const instr_SRAV = cwrap('instr_SRAV', 'number', ['number','number','number']);

  cached = {
    instr_ADD,
    instr_SUB,
    instr_SLT,
    instr_AND,
    instr_OR,
    instr_XOR,
    instr_NOR,
    instr_JR,
    instr_ADDI,
    instr_SLTI,
    instr_ANDI,
    instr_ORI,
    instr_XORI,
    instr_BLTZ,
    instr_BEQ,
    instr_BNE,
    instr_JUMP,
    instr_JAL,
    instr_SLL,
    instr_SRL,
    instr_SRA,
    instr_SLLV,
    instr_SRLV,
    instr_SRAV,
  };
  return cached;
}

export async function Instr() { return m(); }
