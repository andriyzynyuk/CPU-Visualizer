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

    const adder = document.getElementById("Adder_ALU");
    const shifter = document.getElementById("Shifter_ALU");

    const handleAdderClick = () => onNavigate("Adder");
    const handleShifterClick = () => onNavigate("Shifter");

    adder?.addEventListener("click", handleAdderClick);
    shifter?.addEventListener("click", handleShifterClick);

    //Cleanup on unmount
    return () => {
      adder?.removeEventListener("click", handleAdderClick);
      shifter?.removeEventListener("click", handleShifterClick);
    };
  }, [svgContent, onNavigate]);

  return (
    <div className="diagram-container">
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