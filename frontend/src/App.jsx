import { useState } from 'react'
import './App.css'
import ALUView from "./views/ALUView.jsx"
import AdderView from "./views/AdderView.jsx"
import FullAdderView from "./views/FullAdderView.jsx"
import ShifterView from "./views/ShifterView.jsx"
import LogicUnitView from "./views/LogicUnitView.jsx"
import MUX2to1View from "./views/MUX2to1View.jsx"
import MUX4to1View from "./views/MUX4to1View.jsx"

export default function App() {
  const [stack, setStack] = useState([
    { view: "ALU", params: null}
  ]);

  const current = stack[stack.length - 1];

  const navigate = (view, params = null) => {
    setStack((s) => [...s, { view, params }]);
  };

  const goBack = () => {
    setStack((s) => (s.length > 1 ? s.slice(0, -1) : s));
  };

  return (
    <div className="app-root">
      {current.view === "ALU" && (
        <ALUView onNavigate={navigate} />
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
