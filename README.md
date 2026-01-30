# CPU Visualizer & Logic Simulator

**Live Demo:** https://andriyzynyuk.github.io/CPU-Visualizer/

An interactive, educational **CPU visualizer and logic simulator** that lets users explore how a simple CPU works — from high-level architectural blocks down to individual logic gates and signal values.

The project combines **SVG-based hardware diagrams**, **web interactivity**, and a **C++ logic simulation compiled to WebAssembly** to show both the structure *and* behavior of a CPU in real time.

This project is intended to be both a **learning tool** and a **technical showcase**.

---

## Project Overview

CPU Visualizer allows users to:

- Explore a complete CPU design visually
- Zoom and pan through complex diagrams
- Navigate between modules (CPU → ALU → subcomponents)
- Inspect individual wires, gates, and control signals
- Write and execute programs and observe how data flows through the CPU

The project is currently in a **solid, working state**, with most components implemented and functional.

---

## Current Features

- **Fully interactive SVG diagrams**
  - Most CPU components have detailed SVG representations
  - Diagrams are hierarchically organized into modules, submodules, wires, and gates

- **Gate-level structure**
  - All visualized components are constructed from logic gates
  - Every wire in the diagrams carries a value

- **Live signal visualization**
  - Wire and signal values update dynamically during execution
  - Users can observe real signal flow through the CPU

- **Working code editor and execution**
  - Programs can be written directly in the browser
  - Program execution is functional and drives the CPU state

- **Navigation and interaction**
  - Clickable SVG elements for moving between CPU modules
  - Smooth zoom and pan using `react-zoom-pan-pinch`

---

## Tech Stack

- **Frontend:** React
- **Visualization:** SVG
- **Simulation:** C++ compiled to WebAssembly
- **Interaction:** `react-zoom-pan-pinch`
- **Deployment:** GitHub Pages

---

This project is actively being developed, but already provides a functional and detailed view into how a CPU operates at both the architectural and logic-gate levels.
