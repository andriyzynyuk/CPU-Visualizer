import { useState } from 'react'
import './App.css'
import ALUView from "./views/ALUView.jsx"
import AdderView from "./views/AdderView.jsx"

function App() {
  const [view, setView] = useState("ALU");

  return (
    <div className="app-root">
      {view === "ALU" && <ALUView onNavigate={setView} />}
      {view === "Adder" && <AdderView onNavigate={setView} />}
    </div>
  );
}

export default App
