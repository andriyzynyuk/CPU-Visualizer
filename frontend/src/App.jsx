import { useState, useEffect } from 'react'
import './App.css'
import ALUView from "./views/ALUView.jsx"
import AdderView from "./views/AdderView.jsx"
import FullAdderView from "./views/FullAdderView.jsx"
import ShifterView from "./views/ShifterView.jsx"
import LogicUnitView from "./views/LogicUnitView.jsx"
import MUX2to1View from "./views/MUX2to1View.jsx"
import MUX4to1View from "./views/MUX4to1View.jsx"
import CPUView from "./views/CPUView.jsx"
import NextAddrView from "./views/NextAddrView.jsx"
import BranchCondCheckView from "./views/BranchCondCheckView.jsx"

import { getCpuApi } from './cpu/cpuApi';
import { Instr } from './cpu/instructions';

export default function App() {
  const [stack, setStack] = useState([
    { view: "CPU", params: null}
  ]);

  useEffect(() => {
    (async () => {
      const a = await getCpuApi();
      const I = await Instr();
      const cpu = a.cpu_create();
      try {
        const instr = I.instr_ADDI(1, 0, 50);
        a.cpu_load_instruction(cpu, instr);
        a.cpu_first_cycle(cpu);
        const value = a.cpu_get_wire_value(cpu, 'regFile.registers[1]');
        console.log('Register 1 value:', value);
      } finally {
        a.cpu_destroy(cpu);
      }
    })();
  }, []);

  const current = stack[stack.length - 1];

  const navigate = (view, params = null) => {
    setStack((s) => [...s, { view, params }]);
  };

  const goBack = () => {
    setStack((s) => (s.length > 1 ? s.slice(0, -1) : s));
  };

  return (
    <div className="app-root">
      {current.view === "CPU" && (
        <CPUView onNavigate={navigate} />
      )}

      {current.view === "NextAddr" && (
        <NextAddrView
          onNavigate={navigate}
          onBack={goBack}
        />
      )}
      
      {current.view === "BranchCondCheck" && (
        <BranchCondCheckView
          onNavigate={navigate}
          onBack={goBack}
        />
      )}

      {current.view === "ALU" && (
        <ALUView
          onNavigate={navigate}
          onBack={goBack}
        />
      )}

      {current.view === "Shifter" && (
        <ShifterView 
          onNavigate={navigate}
          onBack={goBack}  
        />
      )}

      {current.view === "Adder" && (
        <AdderView 
          onNavigate={navigate}
          onBack={goBack}  
        />
      )}

      {current.view === "FullAdder" && (
        <FullAdderView
          onNavigate={navigate}
          onBack={goBack}  
        />
      )}

      {current.view === "LogicUnit" && (
        <LogicUnitView
          onNavigate={navigate}
          onBack={goBack}
        />
      )}

      {current.view === "MUX2to1" && (
        <MUX2to1View
          onNavigate={navigate}
          onBack={goBack}
        />
      )}

      {current.view === "MUX4to1" && (
        <MUX4to1View
          onNavigate={navigate}
          onBack={goBack}
        />
      )}
    </div>
  );
}
