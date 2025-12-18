# CPU Visualizer & Logic Simulator

An interactive, educational CPU visualization that lets users explore how a simple CPU works 
 - From high-level blocks (ALU, registers, control logic) all the way down to individual logic gates.

The project combines **SVG-based diagrams**, **web interactivity**, and a planned **C++ logic simulation (via WebAssembly)** to show both structure and behavior of a CPU.

---

## Project Goals

- Visually represent a simple CPU architecture
- Allow users to zoom and pan diagrams
- Navigate between modules (CPU → ALU → subcomponents)
- Reveal increasing levels of detail (down to gate-level logic)
- Simulate real signal flow through wires and components

This project is intended to be both a **learning tool** and a **technical showcase**.

---

## Current Features

- SVG-based diagrams for CPU and ALU components
- Zoom and pan interaction using `svg-pan-zoom`
- Clickable SVG elements for navigation between diagrams
- Organized SVG structure with logical grouping (modules, wires, gates)

---

## Planned Features

- C++ simulation of logic gates, wires, and modules
- Cycle-based CPU simulation
- WebAssembly integration for near-native performance
- Live visualization of signal values on wires and gates
- Step-by-step execution and clock control
- React-based frontend for scalable UI architecture
