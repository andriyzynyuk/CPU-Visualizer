import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";

export default function CPUView({ onNavigate }) {
  const [svgContent, setSvgContent] = useState(null);

  useEffect(() => {
    fetch("/svg/CPU.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load CPU.svg", err));
  }, []);

  useEffect(() => {
    if (!svgContent) return;

    const nextAddr = document.getElementById("NextAddr_CPU");
    const mux4to10 = document.getElementById("MUX4to10_CPU");
    const mux2to1 = document.getElementById("MUX2to1_CPU");
    const alu = document.getElementById("ALU_CPU");
    const mux4to11 = document.getElementById("MUX4to11_CPU");

    const handleNextAddrClick = () => onNavigate("NextAddr");
    const handleMUX4to1Click = () => onNavigate("MUX4to1");
    const handleMUX2to1Click = () => onNavigate("MUX2to1");
    const handleALUClick = () => onNavigate("ALU");

    const handleNextAddrMouseEnter = () => {
      if (nextAddr) nextAddr.style.opacity = '0.7';
    };
    const handleNextAddrMouseLeave = () => {
      if (nextAddr) nextAddr.style.opacity = '1';
    };

    const handleMUX4to1MouseEnter = () => {
      if (mux4to10) mux4to10.style.opacity = '0.7';
      if (mux4to11) mux4to11.style.opacity = '0.7';
    };
    const handleMUX4to1MouseLeave = () => {
      if (mux4to10) mux4to10.style.opacity = '1';
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

    mux4to10?.addEventListener("click", handleMUX4to1Click);
    mux4to10?.addEventListener("mouseenter", handleMUX4to1MouseEnter);
    mux4to10?.addEventListener("mouseleave", handleMUX4to1MouseLeave);
    if (mux4to10) mux4to10.style.cursor = 'pointer';

    mux2to1?.addEventListener("click", handleMUX2to1Click);
    mux2to1?.addEventListener("mouseenter", handleMUX2to1MouseEnter);
    mux2to1?.addEventListener("mouseleave", handleMUX2to1MouseLeave);
    if (mux2to1) mux2to1.style.cursor = 'pointer';

    alu?.addEventListener("click", handleALUClick);
    alu?.addEventListener("mouseenter", handleALUMouseEnter);
    alu?.addEventListener("mouseleave", handleALUMouseLeave);
    if (alu) alu.style.cursor = 'pointer';

    mux4to11?.addEventListener("click", handleMUX4to1Click);
    mux4to11?.addEventListener("mouseenter", handleMUX4to1MouseEnter);
    mux4to11?.addEventListener("mouseleave", handleMUX4to1MouseLeave);
    if (mux4to11) mux4to11.style.cursor = 'pointer';

    //Cleanup on unmount
    return () => {
      nextAddr?.removeEventListener("click", handleNextAddrClick);
      nextAddr?.removeEventListener("mouseenter", handleNextAddrMouseEnter);
      nextAddr?.removeEventListener("mouseleave", handleNextAddrMouseLeave);
      mux4to10?.removeEventListener("click", handleMUX4to1Click);
      mux4to10?.removeEventListener("mouseenter", handleMUX4to1MouseEnter);
      mux4to10?.removeEventListener("mouseleave", handleMUX4to1MouseLeave);
      mux2to1?.removeEventListener("click", handleMUX2to1Click);
      mux2to1?.removeEventListener("mouseenter", handleMUX2to1MouseEnter);
      mux2to1?.removeEventListener("mouseleave", handleMUX2to1MouseLeave);
      alu?.removeEventListener("click", handleALUClick);
      alu?.removeEventListener("mouseenter", handleALUMouseEnter);
      alu?.removeEventListener("mouseleave", handleALUMouseLeave);
      mux4to11?.removeEventListener("click", handleMUX4to1Click);
      mux4to11?.removeEventListener("mouseenter", handleMUX4to1MouseEnter);
      mux4to11?.removeEventListener("mouseleave", handleMUX4to1MouseLeave);
    };
  }, [svgContent, onNavigate]);

  return (
    <div className="diagram-container">
        <h2>Central Proccesing Unit</h2>
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