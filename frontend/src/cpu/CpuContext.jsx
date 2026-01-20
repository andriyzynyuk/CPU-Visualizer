import { createContext, useContext, useEffect, useRef, useState, useCallback } from "react";
import { getCpuApi } from "./cpuApi.js";
import { Instr } from "./instructions.js";

const CpuContext = createContext(null);

export function CpuProvider({ children }) {
  const [ready, setReady] = useState(false);
  const [currentCycle, setCurrentCycle] = useState(0);
  const [totalInstructions, setTotalInstructions] = useState(0);
  const [cpuVersion, setCpuVersion] = useState(0); // Force re-render when CPU changes
  const apiRef = useRef(null);
  const cpuRef = useRef(null);
  const instructionsRef = useRef([]);
  const instrLibRef = useRef(null);

  // Function to reset CPU to a specific cycle
  const goToCycle = useCallback(async (targetCycle) => {
    if (!apiRef.current || !instrLibRef.current) return;
    
    const api = apiRef.current;
    
    // Destroy old CPU and create new one
    if (cpuRef.current) {
      api.cpu_destroy(cpuRef.current);
    }
    
    const newCpu = api.cpu_create();
    
    // Reload all instructions
    if (instructionsRef.current.length > 0) {
      api.cpu_load_instructions(newCpu, instructionsRef.current);
    }
    
    // If target cycle is 0, CPU is "off" - no cycles executed
    if (targetCycle === 0) {
      cpuRef.current = newCpu;
      setCurrentCycle(0);
      return;
    }
    
    // Execute first cycle
    api.cpu_first_cycle(newCpu);
    
    // Execute remaining cycles
    for (let i = 1; i < targetCycle; i++) {
      api.cpu_execute_cycle(newCpu);
    }
    
    cpuRef.current = newCpu;
    setCpuVersion(v => v + 1); // Trigger re-render so consumers get new CPU reference
    setCurrentCycle(targetCycle);
  }, []);

  const nextCycle = useCallback(() => {
    if (!apiRef.current || !cpuRef.current) return;
    
    const maxCycles = instructionsRef.current.length;
    if (currentCycle >= maxCycles) return;
    
    if (currentCycle === 0) {
      // First cycle
      apiRef.current.cpu_first_cycle(cpuRef.current);
    } else {
      // Subsequent cycles
      apiRef.current.cpu_execute_cycle(cpuRef.current);
    }
    
    setCpuVersion(v => v + 1); // Trigger re-render so consumers re-read wire values
    setCurrentCycle(prev => prev + 1);
  }, [currentCycle]);

  const prevCycle = useCallback(() => {
    if (currentCycle <= 0) return;
    goToCycle(currentCycle - 1);
  }, [currentCycle, goToCycle]);

  useEffect(() => {
    let cancelled = false;

    (async () => {
      try {
        // Initialize WASM API
        const api = await getCpuApi();
        const instrLib = await Instr();

        // Create CPU and load instructions
        const cpu = api.cpu_create();
        const addi1 = instrLib.instr_ADDI(1, 0, 50);   // r1 = 0 + 50 = 50
        const addi2 = instrLib.instr_ADDI(2, 1, 25);   // r2 = r1 + 25 = 75
        const addi3 = instrLib.instr_ADDI(3, 2, 10);   // r3 = r2 + 10 = 85

        // Store instructions for replay
        instructionsRef.current = [addi1, addi2, addi3];

        // Load all instructions before running the first cycle
        api.cpu_load_instructions(cpu, instructionsRef.current);

        api.cpu_first_cycle(cpu);

        if (cancelled) {
          api.cpu_destroy(cpu);
          return;
        }

        apiRef.current = api;
        cpuRef.current = cpu;
        instrLibRef.current = instrLib;
        setTotalInstructions(instructionsRef.current.length);
        setCurrentCycle(1);
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
      ready,
      currentCycle,
      totalInstructions,
      cpuVersion,
      nextCycle,
      prevCycle,
      goToCycle
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
