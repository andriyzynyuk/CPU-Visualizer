import { useEffect, useState, useRef } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { useCpu } from "../cpu/CpuContext.jsx";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";

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
  { id: "WireSEout_CPU", path: "imm_se" },
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
  { id: "WireALUFunc_CPU", path: "funcClass" },
  { id: "WireDataRead_CPU", path: "dataRead" },
  { id: "WireDataWrite_CPU", path: "dataWrite" },
  { id: "WireBrJump_CPU", path: "PCSrc" }
  //ADDSUB, LOGICFUNC, BrType, ShiftDirection, sh
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

  useEffect(() => {
    if (!svgReady) return;

    const nextAddr = document.getElementById("NextAddr_CPU");
    const mux4to10 = document.getElementById("MUX4to10_CPU");
    const mux2to1 = document.getElementById("MUX2to1_CPU");
    const alu = document.getElementById("ALU_CPU");
    const mux4to11 = document.getElementById("MUX4to11_CPU");

    const handleNextAddrClick = () => onNavigate("NextAddr");
    const handleMUX4to10Click = () => onNavigate("MUX4to1", { basePath: "regDstMux" });
    const handleMUX4to11Click = () => onNavigate("MUX4to1", { basePath: "regInSrc_MUX" });
    const handleMUX2to1Click = () => onNavigate("MUX2to1", { basePath: "ALUSrc_MUX" });
    const handleALUClick = () => onNavigate("ALU");

    const handleNextAddrMouseEnter = () => {
      if (nextAddr) nextAddr.style.opacity = '0.7';
    };
    const handleNextAddrMouseLeave = () => {
      if (nextAddr) nextAddr.style.opacity = '1';
    };

    const handleMUX4to10MouseEnter = () => {
      if (mux4to10) mux4to10.style.opacity = '0.7';
    };
    const handleMUX4to10MouseLeave = () => {
      if (mux4to10) mux4to10.style.opacity = '1';
    };

    const handleMUX4to11MouseEnter = () => {
      if (mux4to11) mux4to11.style.opacity = '0.7';
    };
    const handleMUX4to11MouseLeave = () => {
      if (mux4to11) mux4to11.style.opacity = '1';
    };

    const handleMUX2to1MouseEnter = () => {
      if (mux2to1) mux2to1.style.opacity = '0.7';
    };
    const handleMUX2to1MouseLeave = () => {
      if (mux2to1) mux2to1.style.opacity = '1';
    };

    const handleALUMouseEnter = () => {
      if (alu) alu.style.opacity = '0.7';
    };
    const handleALUMouseLeave = () => {
      if (alu) alu.style.opacity = '1';
    };

    nextAddr?.addEventListener("click", handleNextAddrClick);
    nextAddr?.addEventListener("mouseenter", handleNextAddrMouseEnter);
    nextAddr?.addEventListener("mouseleave", handleNextAddrMouseLeave);
    if (nextAddr) nextAddr.style.cursor = 'pointer';

    mux4to10?.addEventListener("click", handleMUX4to10Click);
    mux4to10?.addEventListener("mouseenter", handleMUX4to10MouseEnter);
    mux4to10?.addEventListener("mouseleave", handleMUX4to10MouseLeave);
    if (mux4to10) mux4to10.style.cursor = 'pointer';

    mux2to1?.addEventListener("click", handleMUX2to1Click);
    mux2to1?.addEventListener("mouseenter", handleMUX2to1MouseEnter);
    mux2to1?.addEventListener("mouseleave", handleMUX2to1MouseLeave);
    if (mux2to1) mux2to1.style.cursor = 'pointer';

    alu?.addEventListener("click", handleALUClick);
    alu?.addEventListener("mouseenter", handleALUMouseEnter);
    alu?.addEventListener("mouseleave", handleALUMouseLeave);
    if (alu) alu.style.cursor = 'pointer';

    mux4to11?.addEventListener("click", handleMUX4to11Click);
    mux4to11?.addEventListener("mouseenter", handleMUX4to11MouseEnter);
    mux4to11?.addEventListener("mouseleave", handleMUX4to11MouseLeave);
    if (mux4to11) mux4to11.style.cursor = 'pointer';

    return () => {
      nextAddr?.removeEventListener("click", handleNextAddrClick);
      nextAddr?.removeEventListener("mouseenter", handleNextAddrMouseEnter);
      nextAddr?.removeEventListener("mouseleave", handleNextAddrMouseLeave);
      mux4to10?.removeEventListener("click", handleMUX4to10Click);
      mux4to10?.removeEventListener("mouseenter", handleMUX4to10MouseEnter);
      mux4to10?.removeEventListener("mouseleave", handleMUX4to10MouseLeave);
      mux2to1?.removeEventListener("click", handleMUX2to1Click);
      mux2to1?.removeEventListener("mouseenter", handleMUX2to1MouseEnter);
      mux2to1?.removeEventListener("mouseleave", handleMUX2to1MouseLeave);
      alu?.removeEventListener("click", handleALUClick);
      alu?.removeEventListener("mouseenter", handleALUMouseEnter);
      alu?.removeEventListener("mouseleave", handleALUMouseLeave);
      mux4to11?.removeEventListener("click", handleMUX4to11Click);
      mux4to11?.removeEventListener("mouseenter", handleMUX4to11MouseEnter);
      mux4to11?.removeEventListener("mouseleave", handleMUX4to11MouseLeave);
    };
  }, [svgReady, onNavigate]);

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