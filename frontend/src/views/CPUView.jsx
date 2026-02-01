import { useEffect, useState, useRef } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { useCpu } from "../cpu/CpuContext.jsx";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";
import { useClickableElements } from "../cpu/useClickableElements.js";

const WIRES = [
  { id: "WireIncrPC_CPU", path: "IncrPC" },
  { id: "WireNextPC_CPU", path: "NextPC" },
  { id: "WirePC_CPU", path: "PC_out" },
  { id: "WireInst_CPU", path: "Instr" },
  { id: "WireJTA_CPU", path: "jta" },
  { id: "WireRS_CPU", path: "rs" },
  { id: "WireRT_CPU", path: "rt" },
  { id: "WireRD_CPU", path: "rd" },
  { id: "Wire31_CPU", path: "returnAddress" },
  { id: "WireImm_CPU", path: "imm" },
  { id: "WireImmSE_CPU", path: "imm_se" },
  { id: "WireOP_CPU", path: "op" },
  { id: "WireFN_CPU", path: "fn" },
  { id: "WireMUX0out_CPU", path: "regDstIn" },
  { id: "Wire(RS)_CPU", path: "rs_out" },
  { id: "Wire(RT)_CPU", path: "rt_out" },
  { id: "WireY_CPU", path: "ALUSrcMux_out" },
  { id: "WireOvfl_CPU", path: "Ovfl" },
  { id: "WireALUout_CPU", path: "ALU_out" },
  { id: "WireRegIn_CPU", path: "RegIn" },
  { id: "WireRegWrite_CPU", path: "regWrite" },
  { id: "WireRegDst_CPU", path: "regDst" },
  { id: "WireRegInSrc_CPU", path: "regInSrc" },
  { id: "WireALUSrc_CPU", path: "ALUSrc" },
  { id: "WireFuncClass_CPU", path: "funcClass" },
  { id: "WireDataRead_CPU", path: "dataRead" },
  { id: "WireDataWrite_CPU", path: "dataWrite" },
  { id: "WireConstVar_CPU", path: "constVar" }, //
  { id: "WireShiftFunc_CPU", path: "shiftFunc" },
  { id: "WireLogicFunc_CPU", path: "logicFunc" },
  { id: "WirePCSrc_CPU", path: "PCSrc" },
  { id: "WireBrType_CPU", path: "BrType" },
  { id: "WireBrType_CPU", path: "BrType" },
  { id: "WireSH_CPU", path: "sh" },
  { id: "WireAddSub_CPU", path: "addSub" },
  { id: "WirePCBR_CPU", path: "PCBR" },
  { id: "WireCUout_CPU", path: "CUout" },
  
  //ADDSUB
];

const SVG_WIDTH = 3099;
const SVG_HEIGHT = 1605;

export default function CPUView({ onNavigate }) {
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
    fetch(`${import.meta.env.BASE_URL}svg/CPU.svg`)
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load CPU.svg", err));
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
    { id: "NextAddr_CPU", onClick: () => onNavigate("NextAddr") },
    { id: "MUX4to10_CPU", onClick: () => onNavigate("MUX4to1", { basePath: "regDstMux" }) },
    { id: "MUX2to1_CPU", onClick: () => onNavigate("MUX2to1", { basePath: "ALUSrc_MUX" }) },
    { id: "ALU_CPU", onClick: () => onNavigate("ALU") },
    { id: "MUX4to11_CPU", onClick: () => onNavigate("MUX4to1", { basePath: "regInSrc_MUX" }) },
  ], [onNavigate]);

  return (
    <div className="diagram-container" onClick={closeTooltip}>
      <WireTooltip tooltip={tooltip} onClose={closeTooltip} />
      
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
        initialScale={0.5}
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