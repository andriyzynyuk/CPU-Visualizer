import { useEffect, useState, useRef } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { useCpu } from "../cpu/CpuContext.jsx";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";
import { useClickableElements } from "../cpu/useClickableElements.js";

const WIRES = [
  { id: "WireX_ALU", path: "alu.x" },
  { id: "WireY_ALU", path: "alu.y" },
  { id: "WireAddSub_ALU", path: "alu.addSub" },
  { id: "WireC0_ALU", path: "alu.addSub" },
  { id: "WireLogicFunction_ALU", path: "alu.logicFunc" },
  { id: "WireFunctionClass_ALU", path: "alu.funcClass" },
  { id: "WireYXOR_ALU", path: "alu.yXOR" },
  { id: "WireShiftedY_ALU", path: "alu.shiftedY" },
  { id: "WireX+Y_ALU", path: "alu.xPlusY" },
  { id: "WireLogic_ALU", path: "alu.logic" },
  { id: "WireMSB_ALU", path: "alu.xPlusYMsb" },
  { id: "WireS_ALU", path: "alu.s" },
  { id: "WireC4_ALU", path: "alu.Cout" },
  { id: "WireVariableAmount_ALU", path: "alu.x5LSB" },
  { id: "WireConstantAmount_ALU", path: "alu.constAmount" },
  { id: "WireConstVar_ALU", path: "alu.constVar" },
  { id: "WireAmount_ALU", path: "alu.amount" },
  { id: "WireShiftFunction_ALU", path: "alu.shiftFunc" }
];

const SVG_WIDTH = 1568;
const SVG_HEIGHT = 1046;

export default function ALUView({ onNavigate, onBack }) {
  const [svgContent, setSvgContent] = useState(null);
  const [svgReady, setSvgReady] = useState(false);
  const [wireValues, setWireValues] = useState({});
  const [tooltip, setTooltip] = useState({ visible: false, x: 0, y: 0, name: "", value: 0 });
  const { api, cpu, ready, currentCycle, currentInstructionText, hasFinished, maxCycles, cpuVersion, nextCycle, prevCycle } = useCpu();
  const svgContainerRef = useRef(null);

  useWireTooltip(svgReady, wireValues, WIRES, setTooltip);

  const closeTooltip = () => setTooltip({ ...tooltip, visible: false });

  const canGoBack = currentCycle > 0;
  const canGoForward = currentCycle < maxCycles;

  useEffect(() => {
    fetch(`${import.meta.env.BASE_URL}svg/ALU.svg`)
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load ALU.svg", err));
  }, []);

  useEffect(() => {
    if (!svgContent || !svgContainerRef.current) return;
    svgContainerRef.current.innerHTML = svgContent;

    const svgElement = svgContainerRef.current.querySelector('svg');
    if (svgElement) {
      svgElement.setAttribute('width', SVG_WIDTH);
      svgElement.setAttribute('height', SVG_HEIGHT);
      svgElement.style.display = 'block';
    }
    setSvgReady(true);
  }, [svgContent]);

  useEffect(() => {
    if (!ready || !api || !cpu) return;

    if (currentCycle === 0 || hasFinished) {
      const values = {};
      WIRES.forEach(({ path }) => {
        values[path] = 0;
      });
      setWireValues(values);
      return;
    }

    const values = {};
    WIRES.forEach(({ path }) => {
      values[path] = api.cpu_get_wire_value(cpu, path);
    });
    setWireValues(values);
  }, [ready, api, cpu, currentCycle, hasFinished, cpuVersion]);

  useEffect(() => {
    if (!svgReady || Object.keys(wireValues).length === 0) return;
    
    WIRES.forEach(({ id, path }) => {
      const el = document.getElementById(id);
      if (!el) {
        console.warn(`Wire element not found: ${id}`);
        return;
      }
      const isActive = (wireValues[path] ?? 0) > 0;
      const color = isActive ? "#00da00" : "#000";
      
      el.setAttribute("fill", color);
      
      const children = el.querySelectorAll('*');
      children.forEach(child => {
        if (child.hasAttribute('fill')) {
          child.setAttribute("fill", color);
        }
      });
    });
  }, [svgReady, wireValues]);

  useClickableElements(svgReady, [
    { id: "MUX2to1_ALU", onClick: () => onNavigate("MUX2to1", { basePath: "alu.shiftAmount" }) },
    { id: "Adder_ALU", onClick: () => onNavigate("Adder", { basePath: "alu.adder" }) },
    { id: "LogicUnit_ALU", onClick: () => onNavigate("LogicUnit") },
    { id: "MUX4to1_ALU", onClick: () => onNavigate("MUX4to1", { basePath: "alu.mux" }) },
  ], [onNavigate]);

  return (
    <div className="diagram-container" onClick={closeTooltip}>
      <WireTooltip tooltip={tooltip} onClose={closeTooltip} />
      
      <button 
        className="back-btn"
        onClick={(e) => { e.stopPropagation(); onBack(); }}
        aria-label="Go back"
      >
        <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2.5" strokeLinecap="round" strokeLinejoin="round">
          <path d="M19 12H5M12 19l-7-7 7-7"/>
        </svg>
      </button>
      
      <div className="clock-control">
        <button 
          className={`clock-btn ${!canGoBack ? 'disabled' : ''}`}
          onClick={(e) => { e.stopPropagation(); if (canGoBack) prevCycle(); }}
          disabled={!canGoBack}
        >
          &lt;
        </button>
        <span className="clock-label">Cycle {currentCycle}</span>
        <button 
          className={`clock-btn ${!canGoForward ? 'disabled' : ''}`}
          onClick={(e) => { e.stopPropagation(); if (canGoForward) nextCycle(); }}
          disabled={!canGoForward}
        >
          &gt;
        </button>
      </div>
      <div className="current-instruction-display">
        Current Instruction: {hasFinished ? 'finished' : (currentInstructionText || 'off')}
      </div>

      <TransformWrapper
        initialScale={0.65}
        minScale={0.2}
        maxScale={20}
        centerOnInit={true}
        limitToBounds={false}
        wheel={{ step: 0.1 }}
        doubleClick={{ disabled: true }}
        panning={{ velocityDisabled: true }}
      >
        {() => (
          <>
            <TransformComponent
              wrapperStyle={{
                width: "100%",
                height: "100%",
              }}
              contentStyle={{
                width: SVG_WIDTH,
                height: SVG_HEIGHT,
              }}
            >
              <div 
                ref={svgContainerRef} 
                className="svg-wrapper"
                style={{
                  width: SVG_WIDTH,
                  height: SVG_HEIGHT,
                }}
              />
            </TransformComponent>
          </>
        )}
      </TransformWrapper>
    </div>
  );
}