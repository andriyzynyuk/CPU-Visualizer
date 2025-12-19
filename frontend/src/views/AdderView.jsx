import { useEffect, useState } from "react";
import { TransformWrapper, TransformComponent } from "react-zoom-pan-pinch";

export default function AdderView({ onNavigate }) {
  const [svgContent, setSvgContent] = useState(null);

  useEffect(() => {
    fetch("/svg/Adder.svg")
      .then((res) => res.text())
      .then(setSvgContent)
      .catch((err) => console.error("Failed to load Adder.svg", err));
  }, []);

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