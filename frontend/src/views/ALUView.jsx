import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";

export default function ALUView({ onNavigate }) {
  const [svgContent, setSvgContent] = useState(null);

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
    };
  }, [svgContent, onNavigate]);

  return (
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
                <div
                    className="svg-wrapper"
                    dangerouslySetInnerHTML={{ __html: svgContent }}
                />
            </TransformComponent>
        </TransformWrapper>
    </div>
  );
}