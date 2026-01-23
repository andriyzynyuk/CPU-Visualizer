import { useState } from 'react'
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
import CodeEditor from "./components/CodeEditor.jsx"
import InfoPage from "./pages/InfoPage.jsx"
import { CpuProvider } from './cpu/CpuContext.jsx';

export default function App() {
  const [stack, setStack] = useState([
    { view: "CPU", params: null}
  ]);
  const [menuOpen, setMenuOpen] = useState(false);
  const [showInfo, setShowInfo] = useState(false);
  const [infoTab, setInfoTab] = useState('welcome');

  const current = stack[stack.length - 1];

  const navigate = (view, params = null) => {
    setStack((s) => [...s, { view, params }]);
  };

  const goBack = () => {
    setStack((s) => (s.length > 1 ? s.slice(0, -1) : s));
  };

  const toggleMenu = () => {
    setMenuOpen((prev) => !prev);
  };

  const goToInfo = (tab = 'welcome') => {
    setInfoTab(tab);
    setShowInfo(true);
  };

  const goToApp = () => {
    setShowInfo(false);
  };

  return (
    <CpuProvider>
      <header className="site-header">
        <button className="menu-btn" onClick={toggleMenu} aria-label="Toggle menu">
          <span className={`hamburger ${menuOpen ? 'open' : ''}`}></span>
        </button>
        <h1 className="header-title" onClick={goToApp} style={{ cursor: 'pointer' }}>CPU Visualizer</h1>
        <a
          className="github-btn"
          href="https://github.com/andriyzynyuk/CPU-Visualizer"
          target="_blank"
          rel="noreferrer"
          aria-label="Open project GitHub repository"
        >
          <svg viewBox="0 0 24 24" width="20" height="20" fill="currentColor" aria-hidden="true">
            <path d="M12 .5C5.65.5.5 5.65.5 12c0 5.1 3.29 9.42 7.86 10.95.58.11.79-.25.79-.56 0-.28-.01-1.02-.02-2-3.2.7-3.88-1.54-3.88-1.54-.53-1.33-1.3-1.69-1.3-1.69-1.06-.72.08-.71.08-.71 1.17.08 1.78 1.2 1.78 1.2 1.04 1.78 2.72 1.27 3.38.97.11-.75.41-1.27.75-1.56-2.55-.29-5.23-1.28-5.23-5.68 0-1.25.44-2.27 1.17-3.07-.12-.29-.51-1.45.11-3.02 0 0 .96-.31 3.15 1.17a10.9 10.9 0 0 1 5.74 0c2.18-1.48 3.14-1.17 3.14-1.17.62 1.57.23 2.73.11 3.02.73.8 1.16 1.82 1.16 3.07 0 4.41-2.69 5.38-5.25 5.66.42.36.8 1.08.8 2.19 0 1.58-.02 2.85-.02 3.24 0 .31.21.68.8.56A10.52 10.52 0 0 0 23.5 12C23.5 5.65 18.35.5 12 .5Z" />
          </svg>
        </a>
        <button className="info-btn" onClick={() => goToInfo('welcome')} aria-label="Info">
          Info
        </button>
      </header>
      
      {showInfo ? (
        <InfoPage onBack={goToApp} initialTab={infoTab} />
      ) : (
        <>
          <CodeEditor menuOpen={menuOpen} onShowHelp={() => goToInfo('programming')} />
      
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
          basePath={current.params?.basePath}
          onNavigate={navigate}
          onBack={goBack}  
        />
      )}

      {current.view === "FullAdder" && (
        <FullAdderView
          bit={current.params?.bit}
          basePath={current.params?.basePath}
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
          basePath={current.params?.basePath}
          onNavigate={navigate}
          onBack={goBack}
        />
      )}

      {current.view === "MUX4to1" && (
        <MUX4to1View
          basePath={current.params?.basePath}
          onNavigate={navigate}
          onBack={goBack}
        />
      )}
      </div>
      </>
      )}
    </CpuProvider>
  );
}
