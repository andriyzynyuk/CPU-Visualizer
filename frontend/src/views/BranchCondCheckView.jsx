import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";

export default function BranchCondCheckView({ onNavigate, onBack }) {
    const [svgContent, setSvgContent] = useState(null);

    useEffect(() => {
        fetch("/svg/BranchCondCheck.svg")
        .then((res) => res.text())
        .then(setSvgContent)
        .catch((err) => console.error("Failed to load BranchCondCheck.svg", err));
    }, []);

    useEffect(() => {
    if (!svgContent) return;

    const adder = document.getElementById("Adder_BranchCondChecker");

    const handleAdderClick = () => onNavigate("Adder");

    const handleAdderMouseEnter = () => {
        if (adder) adder.style.opacity = '0.7';
    };
    const handleAdderMouseLeave = () => {
        if (adder) adder.style.opacity = '1';
    };

    adder?.addEventListener("click", handleAdderClick);
    adder?.addEventListener("mouseenter", handleAdderMouseEnter);
    adder?.addEventListener("mouseleave", handleAdderMouseLeave);
    if (adder) adder.style.cursor = 'pointer';

    return () => {
      adder?.removeEventListener("click", handleAdderClick);
      adder?.removeEventListener("mouseenter", handleAdderMouseEnter);
      adder?.removeEventListener("mouseleave", handleAdderMouseLeave);
    };
}, [svgContent, onNavigate]);

  return (
    <div className="diagram-container">
        <button onClick={onBack}>Back</button>
        <h2>Branch Condition Checker</h2>
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