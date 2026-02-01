# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/).

---

## [Unreleased]

### Added
- 

### Changed
- 

### Fixed
-

### Removed
-

---

## [1.1.0] - 2026-01-31

### Added
- Change Log
- Shifter Instructions: SLL, SRL, SRA, SLLV, SRLV, SRAV
- Control Signals for Shifting Operations in Control Unit (constVar, shiftFunc)
- Wire values for shift signals in ALU for GetWireByPath function
- Control Signals in CPU Diagram: PCSrc, BrType, ConstVar, ShiftFunc, sh
- Backend tests for shifter, alu, instruction, and Control Unit to account for new shifter logic

### Changed
- Shifter Component now has Amount and Function inputs
- Changed ALU, CPU to implement new shifter logic

### Fixed
- SLT test expecting wrong result when x < y
- ALU diagram now has correct components and wires for shifting operations
- JTA Wire in NextAddr is now split into 26 and 30 bit components to account for PC's 4 MSB's
- BrTrue Wire clipping Branch Condition Checker
- Names for Wires
- Wire overlap
- Formatting of program.md

### Removed
- ShiftDirection Wires

---

## [1.0.0] - 2026-01-24

### Added
- Initial release
