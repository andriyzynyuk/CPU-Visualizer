import { useEffect, useCallback } from "react";

/**
 * WireTooltip component that displays wire name and value on click
 * @param {Object} props
 * @param {Object} props.tooltip - Tooltip state {visible, x, y, name, value}
 * @param {Function} props.onClose - Callback to close the tooltip
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
 * Custom hook to handle wire click events and tooltip state
 * @param {string} svgContent - The SVG content string
 * @param {Object} wireValues - Object mapping wire paths to values
 * @param {Array} wires - Array of wire configurations {id, path}
 * @param {Function} setTooltip - State setter for tooltip
 * @returns {void}
 */
export function useWireTooltip(svgContent, wireValues, wires, setTooltip) {
  const handleWireClick = useCallback((e, wireName, wireValue) => {
    e.stopPropagation();
    
    // Get click position relative to the viewport
    const x = e.clientX;
    const y = e.clientY;
    
    // Format the wire name for display (remove prefixes like "Wire" and suffixes like "_CPU")
    const displayName = formatWireName(wireName);
    
    setTooltip({
      visible: true,
      x: x,
      y: y - 60, // Position above the click point
      name: displayName,
      value: wireValue ?? 0,
    });
  }, [setTooltip]);

  useEffect(() => {
    if (!svgContent) return;

    const handlers = [];

    // Add click handlers to all wires
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

    // Also handle generic Wire elements that start with "Wire"
    const allWireElements = document.querySelectorAll('[id^="Wire"]');
    allWireElements.forEach((el) => {
      const wireId = el.id;
      // Check if this wire already has a handler from the WIRES config
      const isConfigured = wires.some(w => w.id === wireId);
      
      if (!isConfigured) {
        const handler = (e) => {
          // For unconfigured wires, show the ID with value "N/A"
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
 * @param {string} wireName - Raw wire ID/name
 * @returns {string} - Formatted display name
 */
function formatWireName(wireName) {
  // Remove common prefixes and suffixes
  let name = wireName
    .replace(/^Wire_?/, "")
    .replace(/_CPU$/, "")
    .replace(/_ALU$/, "")
    .replace(/_LU$/, "")
    .replace(/_NextAddr$/, "")
    .replace(/_Shifter$/, "")
    .replace(/_Adder$/, "");
  
  // Replace underscores with spaces
  name = name.replace(/_/g, " ");
  
  return name || wireName;
}
