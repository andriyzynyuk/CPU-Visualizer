import { initWasm } from './wasmModule';

let api = null;

export async function getCpuApi() {
  if (api) return api;
  const m = await initWasm();

  // Core CPU functions
  const cpu_create = m.cwrap('cpu_create', 'number', []);
  const cpu_destroy = m.cwrap('cpu_destroy', null, ['number']);
  const cpu_first_cycle = m.cwrap('cpu_first_cycle', null, ['number']);
  const cpu_execute_cycle = m.cwrap('cpu_execute_cycle', null, ['number']);
  const cpu_get_wire_value = m.cwrap('cpu_get_wire_value', 'number', ['number', 'string']);

  // Single-instruction load via ccall (no manual malloc needed)
  function cpu_load_instruction(cpu, instr) {
    m.ccall('cpu_load_instruction', null, ['number', 'number'], [cpu, instr]);
  }

  // Multiple-instruction load - writes directly to HEAPU32 and calls C function
  function cpu_load_instructions(cpu, instructions) {
    const count = instructions.length;
    // Allocate space for uint32_t array (4 bytes each)
    const bytesNeeded = count * 4;
    // Find a safe location in the heap - use a high address that won't conflict
    // We'll write directly to HEAPU32 at a temporary location
    const baseOffset = m.HEAPU32.length - count - 100; // Use end of heap
    const ptr = baseOffset * 4; // Convert to byte address
    
    // Copy instructions to WASM memory
    for (let i = 0; i < count; i++) {
      m.HEAPU32[baseOffset + i] = instructions[i];
    }
    
    // Call the C function with cwrap
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

// Convenience helper for your quick smoke test
export async function runAddiSmokeTest() {
  const a = await getCpuApi();
  const instr_ADDI = a.module.cwrap('instr_ADDI', 'number', ['number', 'number', 'number']);
  const cpu = a.cpu_create();
  try {
    const instr = instr_ADDI(1, 0, 50);
    a.cpu_load_instruction(cpu, instr);
    a.cpu_first_cycle(cpu);
    const v = a.cpu_get_wire_value(cpu, 'regFile.registers[1]');
    console.log('Register 1 value:', v);
    return v;
  } finally {
    a.cpu_destroy(cpu);
  }
}
