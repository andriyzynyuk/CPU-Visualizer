import { useEffect, useState, useRef } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { useCpu } from "../cpu/CpuContext.jsx";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";

const WIRES = [
  { id: "Wire(RT)_BranchCondChecker", path: "nextAddr.bccModule.rt" },
  { id: "Wire(RS)_BranchCondChecker", path: "nextAddr.bccModule.rs" },
  { id: "WireBrType_BranchCondChecker", path: "nextAddr.bccModule.BrType" },
  { id: "Wire(RS)MSB_BranchCondChecker", path: "nextAddr.bccModule.rsMSB" },
  { id: "Wire(RS)Not_BranchCondChecker", path: "nextAddr.bccModule.rsNot" },
  { id: "WireConst1_BranchCondChecker", path: "nextAddr.bccModule.cin" },
  { id: "WireAdderResult_BranchCondChecker", path: "nextAddr.bccModule.adderResult" },
  { id: "WireORAdderResults_BranchCondChecker", path: "nextAddr.bccModule.ORAdderResult" },
  { id: "WireBEQ_BranchCondChecker", path: "nextAddr.bccModule.beq" },
  { id: "WireConst0_BranchCondChecker", path: "nextAddr.bccModule.const0" },
  { id: "WireBrTypeMSB_BranchCondChecker", path: "nextAddr.bccModule.BrTypeMSB" },
  { id: "WireBLTZ_BranchCondChecker", path: "nextAddr.bccModule.bltz" },
  { id: "WireBrTrue_BranchCondChecker", path: "nextAddr.bccModule.BrTrue" }
];

const SVG_WIDTH = 1525;
const SVG_HEIGHT = 595;

export default function BranchCondCheckView({ onNavigate, onBack }) {
  const [svgContent, setSvgContent] = useState(null);
  const [svgReady, setSvgReady] = useState(false);
  const [wireValues, setWireValues] = useState({});
  const [tooltip, setTooltip] = useState({ visible: false, x: 0, y: 0, name: "", value: 0 });
  const { api, cpu, ready, currentCycle, currentInstructionText, hasFinished, maxCycles, cpuVersion, nextCycle, prevCycle } = useCpu();
  const svgContainerRef = useRef(null);

  useWireTooltip(svgReady, wireValues, WIRES, setTooltip);

  const closeTooltip = () => setTooltip({ ...tooltip, visible: false });

  const canGoBack = currentCycle > 0;
  const canGoForward = currentCycle < maxCycles && !hasFinished;

  useEffect(() => {
    fetch("/svg/BranchCondCheck.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load BranchCondCheck.svg", err));
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

  useEffect(() => {
    if (!svgReady) return;

    const adder = document.getElementById("Adder_BranchCondChecker");
    const mux4to1 = document.getElementById("MUX");

    const handleAdderClick = () => onNavigate("Adder", { basePath: "nextAddr.bccModule.adder" });
    const handleMUX4to1Click = () => onNavigate("MUX4to1", { basePath: "nextAddr.bccModule.mux" });

    const handleAdderMouseEnter = () => {
      if (adder) adder.style.opacity = '0.7';
    };
    const handleAdderMouseLeave = () => {
      if (adder) adder.style.opacity = '1';
    };

    const handleMUX4to1MouseEnter = () => {
      if (mux4to1) mux4to1.style.opacity = '0.7';
    };
    const handleMUX4to1MouseLeave = () => {
      if (mux4to1) mux4to1.style.opacity = '1';
    };

    adder?.addEventListener("click", handleAdderClick);
    adder?.addEventListener("mouseenter", handleAdderMouseEnter);
    adder?.addEventListener("mouseleave", handleAdderMouseLeave);
    if (adder) adder.style.cursor = 'pointer';

    mux4to1?.addEventListener("click", handleMUX4to1Click);
    mux4to1?.addEventListener("mouseenter", handleMUX4to1MouseEnter);
    mux4to1?.addEventListener("mouseleave", handleMUX4to1MouseLeave);
    if (mux4to1) mux4to1.style.cursor = 'pointer';

    return () => {
      adder?.removeEventListener("click", handleAdderClick);
      adder?.removeEventListener("mouseenter", handleAdderMouseEnter);
      adder?.removeEventListener("mouseleave", handleAdderMouseLeave);
      mux4to1?.removeEventListener("click", handleMUX4to1Click);
      mux4to1?.removeEventListener("mouseenter", handleMUX4to1MouseEnter);
      mux4to1?.removeEventListener("mouseleave", handleMUX4to1MouseLeave);
    };
  }, [svgReady, onNavigate]);

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
        initialScale={1}
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