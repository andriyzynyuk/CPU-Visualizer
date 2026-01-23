import { useEffect, useState, useRef } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { useCpu } from "../cpu/CpuContext.jsx";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";

const WIRE_DEFS = [
    { id: "WireI0_MUX2to1", relPath: "input0" },
    { id: "WireI1_MUX2to1", relPath: "input1" },
    { id: "WireS0_MUX2to1", relPath: "s0" },
    { id: "WireS0Not_MUX2to1", relPath: "s0n" },
    { id: "WireAND0_MUX2to1", relPath: "ANDWire0" },
    { id: "WireAND1_MUX2to1", relPath: "ANDWire1" },
    { id: "WireOut_MUX2to1", relPath: "out" }
];

function buildWires(basePath) {
  return WIRE_DEFS.map(({ id, relPath }) => ({
    id,
    path: basePath ? `${basePath}.${relPath}` : relPath,
  }));
}

const SVG_WIDTH = 889;
const SVG_HEIGHT = 420;

export default function MUX2to1View({ basePath = "", onBack }) {
  const [svgContent, setSvgContent] = useState(null);
  const [svgReady, setSvgReady] = useState(false);
  const [wireValues, setWireValues] = useState({});
  const [tooltip, setTooltip] = useState({ visible: false, x: 0, y: 0, name: "", value: 0 });
  const { api, cpu, ready, currentCycle, currentInstructionText, hasFinished, maxCycles, cpuVersion, nextCycle, prevCycle } = useCpu();
  const svgContainerRef = useRef(null);

  const WIRES = buildWires(basePath);

  useWireTooltip(svgReady, wireValues, WIRES, setTooltip);

  const closeTooltip = () => setTooltip({ ...tooltip, visible: false });

  const canGoBack = currentCycle > 0;
  const canGoForward = currentCycle < maxCycles;

  useEffect(() => {
    fetch("/svg/MUX2to1.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load MUX2to1.svg", err));
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
  }, [ready, api, cpu, currentCycle, hasFinished, cpuVersion, basePath]);

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
                initialScale={0.8}
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