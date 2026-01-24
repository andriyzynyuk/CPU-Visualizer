// Lightweight loader for the Emscripten-generated cpu.js (MODULARIZE factory)
let loadPromise = null;
let moduleInstance = null;

function injectScriptOnce(src) {
  return new Promise((resolve, reject) => {
    const existing = document.querySelector(`script[data-wasm='${src}']`);
    if (existing) {
      existing.addEventListener('load', () => resolve());
      existing.addEventListener('error', (e) => reject(e));
      return;
    }
    const s = document.createElement('script');
    s.src = src;
    s.async = true;
    s.setAttribute('data-wasm', src);
    s.onload = () => resolve();
    s.onerror = (e) => reject(e);
    document.head.appendChild(s);
  });
}

export async function initWasm() {
  if (moduleInstance) return moduleInstance;
  if (!loadPromise) {
    loadPromise = (async () => {
      await injectScriptOnce(`${import.meta.env.BASE_URL}wasm/cpu.js`);
      const m = await window.CPUWasm({
        locateFile: (path) => `${import.meta.env.BASE_URL}wasm/${path}`
      });
      moduleInstance = m;
      return m;
    })();
  }
  return loadPromise;
}

export function getModuleSync() {
  return moduleInstance;
}
