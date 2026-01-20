import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";

// Wire configuration for NextAddr view
const WIRES = [];

export default function NextAddrView({ onNavigate, onBack }) {
    const [svgContent, setSvgContent] = useState(null);
    const [tooltip, setTooltip] = useState({ visible: false, x: 0, y: 0, name: "", value: 0 });

    // Use wire tooltip hook
    useWireTooltip(svgContent, {}, WIRES, setTooltip);

    const closeTooltip = () => setTooltip({ ...tooltip, visible: false });

    useEffect(() => {
        fetch("/svg/NextAddr.svg")
        .then((res) => res.text())
        .then(setSvgContent)
        .catch((err) => console.error("Failed to load NextAddr.svg", err));
    }, []);

    useEffect(() => {
    if (!svgContent) return;

    const branchCondCheck = document.getElementById("BranchConditionChecker_NextAddr");
    const adder = document.getElementById("Adder_NextAddr");
    const mux4to1 = document.getElementById("MUX4to1_NextAddr");

    const handleBranchConditionCheckerClick = () => onNavigate("BranchCondCheck");
    const handleAdderClick = () => onNavigate("Adder");
    const handleMUX4to1Click = () => onNavigate("MUX4to1");

    const handleBranchConditionCheckerMouseEnter = () => {
        if (branchCondCheck) branchCondCheck.style.opacity = '0.7';
    };
    const handleBranchConditionCheckerMouseLeave = () => {
        if (branchCondCheck) branchCondCheck.style.opacity = '1';
    };

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

    branchCondCheck?.addEventListener("click", handleBranchConditionCheckerClick);
    branchCondCheck?.addEventListener("mouseenter", handleBranchConditionCheckerMouseEnter);
    branchCondCheck?.addEventListener("mouseleave", handleBranchConditionCheckerMouseLeave);
    if (branchCondCheck) branchCondCheck.style.cursor = 'pointer';

    adder?.addEventListener("click", handleAdderClick);
    adder?.addEventListener("mouseenter", handleAdderMouseEnter);
    adder?.addEventListener("mouseleave", handleAdderMouseLeave);
    if (adder) adder.style.cursor = 'pointer';

    mux4to1?.addEventListener("click", handleMUX4to1Click);
    mux4to1?.addEventListener("mouseenter", handleMUX4to1MouseEnter);
    mux4to1?.addEventListener("mouseleave", handleMUX4to1MouseLeave);
    if (mux4to1) mux4to1.style.cursor = 'pointer';

    return () => {
      branchCondCheck?.removeEventListener("click", handleBranchConditionCheckerClick);
      branchCondCheck?.removeEventListener("mouseenter", handleBranchConditionCheckerMouseEnter);
      branchCondCheck?.removeEventListener("mouseleave", handleBranchConditionCheckerMouseLeave);

      adder?.removeEventListener("click", handleAdderClick);
      adder?.removeEventListener("mouseenter", handleAdderMouseEnter);
      adder?.removeEventListener("mouseleave", handleAdderMouseLeave);

      mux4to1?.removeEventListener("click", handleMUX4to1Click);
      mux4to1?.removeEventListener("mouseenter", handleMUX4to1MouseEnter);
      mux4to1?.removeEventListener("mouseleave", handleMUX4to1MouseLeave);
    };
}, [svgContent, onNavigate]);

  return (
    <div className="diagram-container" onClick={closeTooltip}>
        <WireTooltip tooltip={tooltip} onClose={closeTooltip} />
        <button onClick={onBack}>Back</button>
        <h2>Next Address</h2>
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