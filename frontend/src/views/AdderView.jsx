import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";

// Wire configuration for Adder view
const WIRES = [];

export default function AdderView({ onNavigate, onBack }) {
  const [svgContent, setSvgContent] = useState(null);
  const [tooltip, setTooltip] = useState({ visible: false, x: 0, y: 0, name: "", value: 0 });

  // Use wire tooltip hook
  useWireTooltip(svgContent, {}, WIRES, setTooltip);

  const closeTooltip = () => setTooltip({ ...tooltip, visible: false });

  useEffect(() => {
    fetch("/svg/Adder.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load Adder.svg", err));
  }, []);

  useEffect(() => {
  if (!svgContent) return;

  const fullAdders = document.querySelectorAll(".full-adder");

  const handleFullAdderClick = (event) => {
    const bitIndex = event.currentTarget.dataset.bit;
    onNavigate("FullAdder", { bit: bitIndex });
  };

  fullAdders.forEach((fa) => {
    fa.addEventListener("click", handleFullAdderClick);
  });

  return () => {
    fullAdders.forEach((fa) => {
      fa.removeEventListener("click", handleFullAdderClick);
    });
  };
}, [svgContent, onNavigate]);

  return (
    <div className="diagram-container" onClick={closeTooltip}>
        <WireTooltip tooltip={tooltip} onClose={closeTooltip} />
        <button onClick={onBack}>Back</button>
        <h2>Adder</h2>
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