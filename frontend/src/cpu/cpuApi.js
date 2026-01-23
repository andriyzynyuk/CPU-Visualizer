import { initWasm } from './wasmModule';

let api = null;

export async function getCpuApi() {
  if (api) return api;
  const m = await initWasm();

  const cpu_create = m.cwrap('cpu_create', 'number', []);
  const cpu_destroy = m.cwrap('cpu_destroy', null, ['number']);
  const cpu_first_cycle = m.cwrap('cpu_first_cycle', null, ['number']);
  const cpu_execute_cycle = m.cwrap('cpu_execute_cycle', null, ['number']);
  const cpu_get_wire_value = m.cwrap('cpu_get_wire_value', 'number', ['number', 'string']);

  function cpu_load_instruction(cpu, instr) {
    m.ccall('cpu_load_instruction', null, ['number', 'number'], [cpu, instr]);
  }

  function cpu_load_instructions(cpu, instructions) {
    const count = instructions.length;
    const bytesNeeded = count * 4;
    const baseOffset = m.HEAPU32.length - count - 100;
    const ptr = baseOffset * 4;
    
    for (let i = 0; i < count; i++) {
      m.HEAPU32[baseOffset + i] = instructions[i];
    }
    
    const loadInstructions = m.cwrap('cpu_load_instructions', null, ['number', 'number', 'number']);
    loadInstructions(cpu, ptr, count);
  }

  api = {
    module: m,
    cpu_create,
    cpu_destroy,
    cpu_first_cycle,
    cpu_execute_cycle,
    cpu_get_wire_value,
    cpu_load_instruction,
    cpu_load_instructions,
  };
  return api;
}
