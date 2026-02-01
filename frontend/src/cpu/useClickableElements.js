import { useEffect } from "react";

/**
 * 
 * @param {boolean} svgReady - Whether the SVG is loaded and ready
 * @param {Array} elements - Array of clickable element definitions
 * @param {Array} deps - Additional dependencies for the effect
 */
export function useClickableElements(svgReady, elements, deps = []) {
  useEffect(() => {
    if (!svgReady) return;

    const cleanups = elements.map(({ id, onClick }) => {
      const el = document.getElementById(id);
      if (!el) return null;

      const handleClick = onClick;
      const handleMouseEnter = () => { el.style.opacity = '0.7'; };
      const handleMouseLeave = () => { el.style.opacity = '1'; };

      el.addEventListener("click", handleClick);
      el.addEventListener("mouseenter", handleMouseEnter);
      el.addEventListener("mouseleave", handleMouseLeave);
      el.style.cursor = 'pointer';

      return () => {
        el.removeEventListener("click", handleClick);
        el.removeEventListener("mouseenter", handleMouseEnter);
        el.removeEventListener("mouseleave", handleMouseLeave);
      };
    });

    return () => {
      cleanups.forEach(cleanup => cleanup?.());
    };
  }, [svgReady, ...deps]);
}
