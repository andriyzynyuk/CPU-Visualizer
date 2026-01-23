import { createContext, useContext, useEffect, useRef, useState, useCallback } from "react";
import { getCpuApi } from "./cpuApi.js";
import { Instr } from "./instructions.js";

const CpuContext = createContext(null);

const MAX_EXECUTION_CYCLES = 1000;

export function CpuProvider({ children }) {
  const [ready, setReady] = useState(false);
  const [currentCycle, setCurrentCycle] = useState(0);
  const [currentInstructionText, setCurrentInstructionText] = useState(null);
  const [hasFinished, setHasFinished] = useState(false);
  const [totalInstructions, setTotalInstructions] = useState(0);
  const [maxCycles, setMaxCycles] = useState(0);
  const [cpuVersion, setCpuVersion] = useState(0);
  const [outputs, setOutputs] = useState([]);
  const apiRef = useRef(null);
  const cpuRef = useRef(null);
  const instructionsRef = useRef([]);
  const instructionTextsRef = useRef([]);
  const finishIndexRef = useRef(-1);
  const instrLibRef = useRef(null);
  const outputInstructionsRef = useRef([]);
  const collectedOutputsRef = useRef(new Set());

  const updateCurrentInstructionText = useCallback((api, cpu, cycle) => {
    if (cycle === 0) {
      setCurrentInstructionText(null);
    } else {
      const pc = api.cpu_get_wire_value(cpu, "PC_out");
      if (finishIndexRef.current !== -1 && pc >= finishIndexRef.current) {
        setCurrentInstructionText(null);
        setHasFinished(true);
      } else {
        const text = instructionTextsRef.current[pc];
        setCurrentInstructionText(text || null);
        setHasFinished(false);
      }
    }
  }, []);

  const hasReachedFinish = useCallback((api, cpu) => {
    if (finishIndexRef.current === -1) return false;
    const pc = api.cpu_get_wire_value(cpu, "PC_out");
    return pc >= finishIndexRef.current;
  }, []);

  const loadInstructions = useCallback(async (instructions, metadata = {}) => {
    if (!apiRef.current) return;
    
    const api = apiRef.current;
    const { finishIndex = -1, outputInstructions = [], instructionTexts = [] } = metadata;
    
    if (cpuRef.current) {
      api.cpu_destroy(cpuRef.current);
    }
    
    const newCpu = api.cpu_create();
    
    instructionsRef.current = instructions;
    instructionTextsRef.current = instructionTexts;
    finishIndexRef.current = finishIndex;
    outputInstructionsRef.current = outputInstructions;
    
    if (instructions.length > 0) {
      api.cpu_load_instructions(newCpu, instructions);
    }
    
    cpuRef.current = newCpu;
    setTotalInstructions(instructions.length);
    
    setMaxCycles(instructions.length > 0 ? MAX_EXECUTION_CYCLES : 0);
    setCpuVersion(v => v + 1);
    setCurrentCycle(0);
    setCurrentInstructionText(null);
    setHasFinished(false);
    setOutputs([]);
    collectedOutputsRef.current = new Set();
  }, []);

  const collectOutputsForCycle = useCallback((api, cpu, cycleNum, collectedSet) => {
    const newOutputs = [];
    const pc = api.cpu_get_wire_value(cpu, "PC_out");
    
    for (const outputInstr of outputInstructionsRef.current) {
      if (pc >= outputInstr.instrIndex && !collectedSet.has(outputInstr.instrIndex)) {
        const regValue = api.cpu_get_wire_value(cpu, `regFile.registers[${outputInstr.register}]`);
        newOutputs.push({
          register: outputInstr.register,
          value: regValue,
          cycle: cycleNum,
          lineNum: outputInstr.lineNum
        });
        collectedSet.add(outputInstr.instrIndex);
      }
    }
    return newOutputs;
  }, []);

  const goToCycle = useCallback(async (targetCycle) => {
    if (!apiRef.current || !instrLibRef.current) return;
    
    const api = apiRef.current;
    
    if (cpuRef.current) {
      api.cpu_destroy(cpuRef.current);
    }
    
    const newCpu = api.cpu_create();
    
    if (instructionsRef.current.length > 0) {
      api.cpu_load_instructions(newCpu, instructionsRef.current);
    }
    
    setOutputs([]);
    
    const collectedSet = new Set();
    
    if (targetCycle === 0) {
      cpuRef.current = newCpu;
      collectedOutputsRef.current = collectedSet;
      setCurrentCycle(0);
      setCurrentInstructionText(null);
      setHasFinished(false);
      return;
    }
    
    api.cpu_first_cycle(newCpu);
    
    const accumulatedOutputs = [];
    accumulatedOutputs.push(...collectOutputsForCycle(api, newCpu, 1, collectedSet));
    
    let actualCycle = 1;
    for (let i = 1; i < targetCycle; i++) {
      if (hasReachedFinish(api, newCpu)) break;
      api.cpu_execute_cycle(newCpu);
      actualCycle = i + 1;
      accumulatedOutputs.push(...collectOutputsForCycle(api, newCpu, i + 1, collectedSet));
    }
    
    cpuRef.current = newCpu;
    collectedOutputsRef.current = collectedSet;
    setOutputs(accumulatedOutputs);
    setCpuVersion(v => v + 1);
    setCurrentCycle(actualCycle);
    updateCurrentInstructionText(api, newCpu, actualCycle);
  }, [collectOutputsForCycle, updateCurrentInstructionText, hasReachedFinish]);

  const nextCycle = useCallback(() => {
    if (!apiRef.current || !cpuRef.current) return;
    
    const api = apiRef.current;
    const cpu = cpuRef.current;
    
    // Safety limit to prevent infinite loops
    if (currentCycle >= MAX_EXECUTION_CYCLES) return;
    
    const nextCycleNum = currentCycle + 1;
    const hasAlreadyFinished = hasReachedFinish(api, cpu);
    
    // Only execute cycle if program hasn't finished yet
    if (!hasAlreadyFinished) {
      if (currentCycle === 0) {
        api.cpu_first_cycle(cpu);
      } else {
        api.cpu_execute_cycle(cpu);
      }
      
      const newOutputs = collectOutputsForCycle(api, cpu, nextCycleNum, collectedOutputsRef.current);
      if (newOutputs.length > 0) {
        setOutputs(prev => [...prev, ...newOutputs]);
      }
    }
    
    setCpuVersion(v => v + 1);
    setCurrentCycle(nextCycleNum);
    updateCurrentInstructionText(api, cpu, nextCycleNum);
  }, [currentCycle, collectOutputsForCycle, updateCurrentInstructionText, hasReachedFinish]);

  const prevCycle = useCallback(() => {
    if (currentCycle <= 0) return;
    goToCycle(currentCycle - 1);
  }, [currentCycle, goToCycle]);

  useEffect(() => {
    let cancelled = false;

    (async () => {
      try {
        const api = await getCpuApi();
        const instrLib = await Instr();

        const cpu = api.cpu_create();

        instructionsRef.current = [];

        if (cancelled) {
          api.cpu_destroy(cpu);
          return;
        }

        apiRef.current = api;
        cpuRef.current = cpu;
        instrLibRef.current = instrLib;
        setTotalInstructions(0);
        setMaxCycles(0);
        setCurrentCycle(0);
        setReady(true);
      } catch (err) {
        console.error("[CpuContext] Error:", err);
      }
    })();

    return () => {
      cancelled = true;
      if (apiRef.current && cpuRef.current) {
        apiRef.current.cpu_destroy(cpuRef.current);
      }
    };
  }, []);

  return (
    <CpuContext.Provider value={{ 
      api: apiRef.current, 
      cpu: cpuRef.current, 
      instrLib: instrLibRef.current,
      ready,
      currentCycle,
      currentInstructionText,
      hasFinished,
      totalInstructions,
      maxCycles,
      outputs,
      cpuVersion,
      nextCycle,
      prevCycle,
      goToCycle,
      loadInstructions
    }}>
      {children}
    </CpuContext.Provider>
  );
}

export function useCpu() {
  const context = useContext(CpuContext);
  if (!context) {
    throw new Error("useCpu must be used within a CpuProvider");
  }
  return context;
}
