import { useEffect, useCallback } from "react";

/**
 * displays wire name and value on click
 * @param {Object} props
 * @param {Object} props.tooltip
 * @param {Function} props.onClose
 */
export function WireTooltip({ tooltip, onClose }) {
  if (!tooltip.visible) return null;

  return (
    <div
      className="wire-tooltip"
      style={{
        left: tooltip.x,
        top: tooltip.y,
      }}
    >
      <button className="wire-tooltip-close" onClick={onClose}>
        ×
      </button>
      <div className="wire-tooltip-name">{tooltip.name}</div>
      <div className="wire-tooltip-value">
        Value: <span className="wire-tooltip-value-num">{tooltip.value}</span>
      </div>
    </div>
  );
}

/**
 * handle wire click events and tooltip state
 * @param {string} svgContent
 * @param {Object} wireValues
 * @param {Array} wires
 * @param {Function} setTooltip
 * @returns {void}
 */
export function useWireTooltip(svgContent, wireValues, wires, setTooltip) {
  const handleWireClick = useCallback((e, wireName, wireValue) => {
    e.stopPropagation();
    
    const x = e.clientX;
    const y = e.clientY;
    
    const displayName = formatWireName(wireName);
    
    setTooltip({
      visible: true,
      x: x,
      y: y - 6,
      name: displayName,
      value: wireValue ?? 0,
    });
  }, [setTooltip]);

  useEffect(() => {
    if (!svgContent) return;

    const handlers = [];

    wires.forEach(({ id, path }) => {
      const el = document.getElementById(id);
      if (!el) return;

      const handler = (e) => {
        const value = wireValues[path] ?? 0;
        handleWireClick(e, id, value);
      };

      el.addEventListener("click", handler);
      handlers.push({ el, handler });
    });

    const allWireElements = document.querySelectorAll('[id^="Wire"]');
    allWireElements.forEach((el) => {
      const wireId = el.id;
      const isConfigured = wires.some(w => w.id === wireId);
      
      if (!isConfigured) {
        const handler = (e) => {
          handleWireClick(e, wireId, "N/A");
        };
        el.addEventListener("click", handler);
        handlers.push({ el, handler });
      }
    });

    return () => {
      handlers.forEach(({ el, handler }) => {
        el.removeEventListener("click", handler);
      });
    };
  }, [svgContent, wireValues, wires, handleWireClick]);
}

/**
 * Format wire name for display
 * @param {string} wireName
 * @returns {string}
 */
function formatWireName(wireName) {
  let name = wireName
    .replace(/^Wire_?/, "")
    .replace(/_CPU$/, "")
    .replace(/_ALU$/, "")
    .replace(/_LU$/, "")
    .replace(/_NextAddr$/, "")
    .replace(/_Shifter$/, "")
    .replace(/_Adder$/, "");
  
  name = name.replace(/_/g, " ");
  
  return name || wireName;
}
