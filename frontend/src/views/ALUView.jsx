import { useEffect, useState, useRef } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { simulateALU } from "../sim/alu";

export default function ALUView({ onNavigate }) {
  const [svgContent, setSvgContent] = useState("");
  const [aluState, setAluState] = useState(null);
  const [tooltip, setTooltip] = useState(null);

  // Input states
  const [x, setX] = useState('0001');
  const [y, setY] = useState('0000');
  const [shiftDirection, setShiftDirection] = useState('1');
  const [AddSub, setAddSub] = useState('1');
  const [logicFunc, setLogicFunc] = useState('01');
  const [funcClass, setFuncClass] = useState('10');
  const [constAmount, setConstAmount] = useState('01');
  const [constVar, setConstVar] = useState('0');

  const svgContainerRef = useRef(null);

  useEffect(() => {
    if (!svgContent || !svgContainerRef.current) return;
    svgContainerRef.current.innerHTML = svgContent;
  }, [svgContent]);
  

  useEffect(() => {
    fetch("/svg/ALU.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load ALU.svg", err));
  }, []);

  useEffect(() => {
    if (!svgContent) return;

    const shifter = document.getElementById("Shifter_ALU");
    const adder = document.getElementById("Adder_ALU");
    const logicUnit = document.getElementById("LogicUnit_ALU");
    const mux2to1 = document.getElementById("MUX2to1_ALU");
    const mux4to1 = document.getElementById("MUX4to1_ALU");

    const handleShifterClick = () => onNavigate("Shifter");
    const handleAdderClick = () => onNavigate("Adder");
    const handleLogicUnitClick = () => onNavigate("LogicUnit");
    const handleMux2to1Click = () => onNavigate("MUX2to1");
    const handleMux4to1Click = () => onNavigate("MUX4to1");

    const handleShifterMouseEnter = () => {
      if (shifter) shifter.style.opacity = '0.7';
    };
    const handleShifterMouseLeave = () => {
      if (shifter) shifter.style.opacity = '1';
    };

    const handleAdderMouseEnter = () => {
      if (adder) adder.style.opacity = '0.7';
    };
    const handleAdderMouseLeave = () => {
      if (adder) adder.style.opacity = '1';
    };

    const handleLogicUnitMouseEnter = () => {
      if (logicUnit) logicUnit.style.opacity = '0.7';
    };
    const handleLogicUnitMouseLeave = () => {
      if (logicUnit) logicUnit.style.opacity = '1';
    };

    const handleMux2to1MouseEnter = () => {
      if (mux2to1) mux2to1.style.opacity = '0.7';
    };
    const handleMux2to1MouseLeave = () => {
      if (mux2to1) mux2to1.style.opacity = '1';
    };

    const handleMux4to1MouseEnter = () => {
      if (mux4to1) mux4to1.style.opacity = '0.7';
    };
    const handleMux4to1MouseLeave = () => {
      if (mux4to1) mux4to1.style.opacity = '1';
    };

    shifter?.addEventListener("click", handleShifterClick);
    shifter?.addEventListener("mouseenter", handleShifterMouseEnter);
    shifter?.addEventListener("mouseleave", handleShifterMouseLeave);
    if (shifter) shifter.style.cursor = 'pointer';

    adder?.addEventListener("click", handleAdderClick);
    adder?.addEventListener("mouseenter", handleAdderMouseEnter);
    adder?.addEventListener("mouseleave", handleAdderMouseLeave);
    if (adder) adder.style.cursor = 'pointer';

    logicUnit?.addEventListener("click", handleLogicUnitClick);
    logicUnit?.addEventListener("mouseenter", handleLogicUnitMouseEnter);
    logicUnit?.addEventListener("mouseleave", handleLogicUnitMouseLeave);
    if (logicUnit) logicUnit.style.cursor = 'pointer';

    mux2to1?.addEventListener("click", handleMux2to1Click);
    mux2to1?.addEventListener("mouseenter", handleMux2to1MouseEnter);
    mux2to1?.addEventListener("mouseleave", handleMux2to1MouseLeave);
    if (mux2to1) mux2to1.style.cursor = 'pointer';

    mux4to1?.addEventListener("click", handleMux4to1Click);
    mux4to1?.addEventListener("mouseenter", handleMux4to1MouseEnter);
    mux4to1?.addEventListener("mouseleave", handleMux4to1MouseLeave);
    if (mux4to1) mux4to1.style.cursor = 'pointer';

    // Wire hover effects
    const wires = document.querySelectorAll("[data-wire]");
    const wireHandlers = [];

    wires.forEach((wire) => {
      const handleWireMouseEnter = () => {
        if (wire.style.fill === "lime") {
          wire.style.fill = "green";
        } else {
          wire.style.fill = "grey";
        }
      };
      const handleWireMouseLeave = () => {
        if (wire.style.fill === "green") {
          wire.style.fill = "lime";
        } else {
          wire.style.fill = "black";
        }
      };

      wire.addEventListener("mouseenter", handleWireMouseEnter);
      wire.addEventListener("mouseleave", handleWireMouseLeave);
      wire.style.cursor = 'pointer';

      wireHandlers.push({ element: wire, enter: handleWireMouseEnter, leave: handleWireMouseLeave });
    });

    //Cleanup on unmount
    return () => {
      shifter?.removeEventListener("click", handleShifterClick);
      shifter?.removeEventListener("mouseenter", handleShifterMouseEnter);
      shifter?.removeEventListener("mouseleave", handleShifterMouseLeave);
      adder?.removeEventListener("click", handleAdderClick);
      adder?.removeEventListener("mouseenter", handleAdderMouseEnter);
      adder?.removeEventListener("mouseleave", handleAdderMouseLeave);
      logicUnit?.removeEventListener("click", handleLogicUnitClick);
      logicUnit?.removeEventListener("mouseenter", handleLogicUnitMouseEnter);
      logicUnit?.removeEventListener("mouseleave", handleLogicUnitMouseLeave);
      mux2to1?.removeEventListener("click", handleMux2to1Click);
      mux2to1?.removeEventListener("mouseenter", handleMux2to1MouseEnter);
      mux2to1?.removeEventListener("mouseleave", handleMux2to1MouseLeave);
      mux4to1?.removeEventListener("click", handleMux4to1Click);
      mux4to1?.removeEventListener("mouseenter", handleMux4to1MouseEnter);
      mux4to1?.removeEventListener("mouseleave", handleMux4to1MouseLeave);

      wireHandlers.forEach(({ element, enter, leave }) => {
        element.removeEventListener("mouseenter", enter);
        element.removeEventListener("mouseleave", leave);
      });
    };
  }, [svgContent, onNavigate]);

  //simulation
  useEffect(() => {
    const state = simulateALU({
      x: parseInt(x, 2),
      y: parseInt(y, 2),
      shiftDirection: parseInt(shiftDirection, 2),
      AddSub: parseInt(AddSub, 2),
      logicFunc: parseInt(logicFunc, 2),
      funcClass: parseInt(funcClass, 2),
      constAmount: parseInt(constAmount, 2),
      constVar: parseInt(constVar, 2),
    });

    setAluState(state);
  }, [x, y, shiftDirection, AddSub, logicFunc, funcClass, constAmount, constVar]);

  useEffect(() => {
      if (!aluState || !svgContent) return;

      //input
      setWireActive("WireX_ALU", aluState.inputs.x);
      setWireActive("WireY_ALU", aluState.inputs.y);
      setWireActive("WireShiftDirection_ALU", aluState.inputs.shiftDirection);
      setWireActive("WireAddSub_ALU", aluState.inputs.AddSub);
      setWireActive("WireLogicFunction_ALU", aluState.inputs.logicFunc);
      setWireActive("WireFunctionClass_ALU", aluState.inputs.funcClass);
      setWireActive("WireConstantAmount_ALU", aluState.inputs.constAmount);
      setWireActive("WireConstVar_ALU", aluState.inputs.constVar);

      //internal
      setWireActive("WireShiftedY_ALU", aluState.internal.shiftedY);
      setWireActive("WireYXOR_ALU", aluState.internal.xorY);
      setWireActive("WireX+Y_ALU", aluState.internal.xPlusY);
      setWireActive("WireLogic_ALU", aluState.internal.logic);
      setWireActive("WireC4_ALU", aluState.internal.carry);
      setWireActive("WireVariableAmount_ALU", aluState.internal.variableAmount);
      setWireActive("WireAmount_ALU", aluState.internal.amount);
      setWireActive("WireMSB_ALU", aluState.internal.msb);

      //output
      setWireActive("WireS_ALU", aluState.output.s);
  }, [aluState, svgContent]);

  //Wire Tool Tip
  useEffect(() => {
    if (!svgContent || !aluState) return;

    const svg = document.querySelector(".svg-wrapper svg");
    if (!svg) return;

    const handleClick = (e) => {
      const wireEl = e.target.closest("[data-wire]");
      if (!wireEl) return;

      const wireName = wireEl.dataset.wire;

      const value =
        aluState.inputs[wireName] ??
        aluState.internal[wireName] ??
        aluState.output[wireName];

      if (value === undefined) return;

      setTooltip({
        wire: wireName,
        value,
      });
    };

    svg.addEventListener("click", handleClick);

    return () => {
      svg.removeEventListener("click", handleClick);
    };
  }, [svgContent, aluState]);

  return (
    <>
    <div style={{ display: 'flex', gap: '20px', alignItems: 'flex-start' }}>
      <div className="inputs-panel" style={{ minWidth: '250px', padding: '10px', border: '1px solid #ccc', borderRadius: '8px' }}>
        <h3>ALU Inputs</h3>
        <div style={{ marginBottom: '10px' }}>
          <label>X (4-bit): </label>
          <input
            type="text"
            value={x}
            onChange={(e) => setX(e.target.value.replace(/[^01]/g, '').slice(0, 4))}
            style={{ width: '60px', fontFamily: 'monospace' }}
          />
        </div>
        <div style={{ marginBottom: '10px' }}>
          <label>Y (4-bit): </label>
          <input
            type="text"
            value={y}
            onChange={(e) => setY(e.target.value.replace(/[^01]/g, '').slice(0, 4))}
            style={{ width: '60px', fontFamily: 'monospace' }}
          />
        </div>
        <div style={{ marginBottom: '10px' }}>
          <label>Shift Direction (1-bit): </label>
          <input
            type="text"
            value={shiftDirection}
            onChange={(e) => setShiftDirection(e.target.value.replace(/[^01]/g, '').slice(0, 1))}
            style={{ width: '20px', fontFamily: 'monospace' }}
          />
        </div>
        <div style={{ marginBottom: '10px' }}>
          <label>Add/Sub (1-bit): </label>
          <input
            type="text"
            value={AddSub}
            onChange={(e) => setAddSub(e.target.value.replace(/[^01]/g, '').slice(0, 1))}
            style={{ width: '20px', fontFamily: 'monospace' }}
          />
        </div>
        <div style={{ marginBottom: '10px' }}>
          <label>Logic Func (2-bit): </label>
          <input
            type="text"
            value={logicFunc}
            onChange={(e) => setLogicFunc(e.target.value.replace(/[^01]/g, '').slice(0, 2))}
            style={{ width: '40px', fontFamily: 'monospace' }}
          />
        </div>
        <div style={{ marginBottom: '10px' }}>
          <label>Func Class (2-bit): </label>
          <input
            type="text"
            value={funcClass}
            onChange={(e) => setFuncClass(e.target.value.replace(/[^01]/g, '').slice(0, 2))}
            style={{ width: '40px', fontFamily: 'monospace' }}
          />
        </div>
        <div style={{ marginBottom: '10px' }}>
          <label>Const Amount (2-bit): </label>
          <input
            type="text"
            value={constAmount}
            onChange={(e) => setConstAmount(e.target.value.replace(/[^01]/g, '').slice(0, 2))}
            style={{ width: '40px', fontFamily: 'monospace' }}
          />
        </div>
        <div style={{ marginBottom: '10px' }}>
          <label>Const Var (1-bit): </label>
          <input
            type="text"
            value={constVar}
            onChange={(e) => setConstVar(e.target.value.replace(/[^01]/g, '').slice(0, 1))}
            style={{ width: '20px', fontFamily: 'monospace' }}
          />
        </div>
      </div>
      <div className="diagram-container">
        <h2>Arithmetic Logic Unit</h2>

        <TransformWrapper 
            minScale={0.3}
            maxScale={20}
            centerOnInit
            wheel={{ step: 0.1 }}
            doubleClick={{ disabled: true }}
        >
            <TransformComponent>
                <div ref={svgContainerRef} className="svg-wrapper" />
            </TransformComponent>
        </TransformWrapper>
      </div>
    </div>

    {tooltip && (
      <div
        className="wire-tooltip"
        style={{
          position: "fixed",
          top: 20,
          right: 20,
          background: "#111",
          color: "#0f0",
          padding: "10px 12px",
          borderRadius: "6px",
          fontFamily: "monospace",
          fontSize: "13px",
          zIndex: 2000,
          minWidth: "160px",
        }}
      >
        <div
          style={{
            display: "flex",
            justifyContent: "space-between",
            alignItems: "center",
            marginBottom: "6px",
          }}
        >
          <strong>{tooltip.wire}</strong>
          <button
            onClick={() => setTooltip(null)}
            style={{
              background: "none",
              border: "none",
              color: "#0f0",
              cursor: "pointer",
              fontSize: "14px",
            }}
          >
            ✕
          </button>
        </div>

        <div>
          <strong>Binary:</strong>{" "}
          {tooltip.value.toString(2).padStart(4, "0")}
        </div>
        <div>
          <strong>Decimal:</strong> {tooltip.value}
        </div>
      </div>
    )}
    </>
  );
}

function setWireActive(id, value) {
  const el = document.getElementById(id);
  if (!(el instanceof SVGElement)) return;

  const active = value !== 0;

  el.style.fill = active ? "lime" : "black";
}
