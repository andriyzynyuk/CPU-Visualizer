import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";
import { WireTooltip, useWireTooltip } from "../cpu/WireTooltip.jsx";

// Wire configuration for FullAdder view
const WIRES = [];

export default function FullAdderView({ bit, onBack }) {
  const [svgContent, setSvgContent] = useState(null);
  const [tooltip, setTooltip] = useState({ visible: false, x: 0, y: 0, name: "", value: 0 });

  // Use wire tooltip hook
  useWireTooltip(svgContent, {}, WIRES, setTooltip);

  const closeTooltip = () => setTooltip({ ...tooltip, visible: false });

  useEffect(() => {
    fetch("/svg/FullAdder.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load FullAdder.svg", err));
  }, []);

  return (
    <div className="diagram-container" onClick={closeTooltip}>
        <WireTooltip tooltip={tooltip} onClose={closeTooltip} />
        <button onClick={onBack}>Back</button>
        <h2>Full Adder (bit{bit})</h2>
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