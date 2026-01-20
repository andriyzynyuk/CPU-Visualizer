import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";

// Wire configuration for LogicUnit view
const WIRES = [];

export default function LogicUnitView({ onNavigate, onBack }) {
  const [svgContent, setSvgContent] = useState(null);
  const [tooltip, setTooltip] = useState({ visible: false, x: 0, y: 0, name: "", value: 0 });

  // Use wire tooltip hook
  useWireTooltip(svgContent, {}, WIRES, setTooltip);

  const closeTooltip = () => setTooltip({ ...tooltip, visible: false });

  useEffect(() => {
    fetch("/svg/LogicUnit.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load LogicUnit.svg", err));
  }, []);

  useEffect(() => {
    if (!svgContent) return;

    const mux4to1 = document.getElementById("MUX4to1_LU");

    const handleMux4to1Click = () => onNavigate("MUX4to1");

    mux4to1?.addEventListener("click", handleMux4to1Click);

    //Cleanup on unmount
    return () => {
      mux4to1?.removeEventListener("click", handleMux4to1Click);
    };
  }, [svgContent, onNavigate]);

  return (
    <div className="diagram-container" onClick={closeTooltip}>
        <WireTooltip tooltip={tooltip} onClose={closeTooltip} />
        <button onClick={onBack}>Back</button>
        <h2>Logic Unit</h2>
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