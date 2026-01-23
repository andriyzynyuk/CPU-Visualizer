
## Programming Information

The code editor can be found in the side menu on the left. You can open the side menu using the button in the top-left corner of the page.

The assembly language used in this simulator is inspired by **MIPS**, but simplified. Do not expect unmodified MIPS assembly code to work here; however, with small changes it should usually be compatible.

Below you will find tables listing all currently available instructions that can be used in the code editor. Further down, each instruction is explained in more detail with usage examples.

## Registers

Unlike standard MIPS, registers have no special names and can only be accessed by their index (e.g., `0`, `1`, etc.).

- There are no restrictions on reading from or writing to registers.
- The return address for `JAL` is stored in **register 31**.
- All registers are initialized to `0`.
- There are 32 registers total. (0-31)

## Labels

Similar to MIPS, labels can be used to mark locations in code. Labels are optional.

- Code execution always proceeds from top to bottom unless altered by a branch or jump.
- Label format:  
label:

Refer to the default program for examples of label usage.

## Comments

Comments can be use added using '#'.

## System Instructions

These instructions are unique to **CPU Visualizer**.

| Instruction | Description                         | Format          |
|------------|-------------------------------------|-----------------|
| `finish`   | Specify where program execution ends | `finish`        |
| `output`   | Output the value of a register       | `output(reg#)` |

---

## R-Type Instructions

| Instruction | Description                             | Format           |
|------------|-----------------------------------------|------------------|
| `ADD`      | Add two register values                 | `add rd, rs, rt` |
| `SUB`      | Subtract two register values            | `sub rd, rs, rt` |
| `SLT`      | Set if one register is less than another| `slt rd, rs, rt` |
| `AND`      | Bitwise AND of two registers            | `and rd, rs, rt` |
| `OR`       | Bitwise OR of two registers             | `or rd, rs, rt`  |
| `XOR`      | Bitwise XOR of two registers            | `xor rd, rs, rt` |
| `NOR`      | Bitwise NOR of two registers            | `nor rd, rs, rt` |

---

## I-Type Instructions

| Instruction | Description                             | Format              |
|------------|-----------------------------------------|---------------------|
| `ADDI`     | Add an immediate value to a register    | `addi rt, rs, imm`  |
| `SLTI`     | Set if register is less than immediate  | `slti rt, rs, imm`  |
| `ANDI`     | Bitwise AND register with immediate     | `andi rt, rs, imm`  |
| `ORI`      | Bitwise OR register with immediate      | `ori rt, rs, imm`   |
| `XORI`     | Bitwise XOR register with immediate     | `xori rt, rs, imm`  |

---

## Branch Instructions

| Instruction | Description               | Format                  |
|------------|---------------------------|--------------------------|
| `BLTZ`     | Branch if register < 0    | `bltz rs, label`        |
| `BEQ`      | Branch if equal           | `beq rs, rt, label`     |
| `BNE`      | Branch if not equal       | `bne rs, rt, label`     |

---

## Jump Instructions

| Instruction | Description                                  | Format        |
|------------|----------------------------------------------|---------------|
| `J`        | Jump to label                                | `j label`     |
| `JR`       | Jump to address stored in register           | `jr rs`       |
| `JAL`      | Jump to label and save return address        | `jal label`   |

## In-Depth

Here you will find detailed information about each Instruction available to use.

## System Instructions

**Finish**
The `finish` instruction is required to be written at least once, and marks where program execution ends.
example:
`finish`
 - meaning: When Program Counters gets to 'finish', program execution will end

**Output**
The `output` instruction displays the value of a specified register. This instructions has no influence on the CPU, and is solely used for convenience.
example:
`output(26)`
 - meaning: Displays the value of register 26

## R-Type Instructions

**ADD**
The `add` instruction adds values of registers rs and rt, and stores the result in register rd
example:
`add 2, 0, 1`
 - meaning: add values of register 0, 1, store result in register 2

**SUB**
The `sub` instruction subtracts values of registers rs and rt, and stores the result in register rd
example:
`sub 2, 0, 1`
 - meaning: subtract values of register 0, 1, store result in register 2. Note that value of reg 1 is subtracted from value of reg 0

**SLT**
The `slt` instruction checks if the value of register rs is less than the value of register rt. If true, register rd is set to 1, else set to 0
example:
`slt 2, 0, 1`
 - meaning: if value of register 0 is less than that of register 1, set register 2 to value 1, else set register 2 to value 0.

**AND**
The `and` instruction performs the bitwise AND operation on values in register rs and rt. The result is stored in register rd.
example:
`and 2, 0, 1`
 - meaning: Register 0 AND Register 1. Store result in Register 2 

**OR**
The `or` instruction performs the bitwise OR operation on values in register rs and rt. The result is stored in register rd.
example:
`or 2, 0, 1`
 - meaning: Register 0 OR Register 1. Store result in Register 2 

**XOR**
The `xor` instruction performs the bitwise XOR operation on values in register rs and rt. The result is stored in register rd.
example:
`xor 2, 0, 1`
 - meaning: Register 0 XOR Register 1. Store result in Register 2

**NOR**
The `nor` instruction performs the bitwise NOR operation on values in register rs and rt. The result is stored in register rd.
example:
`nor 2, 0, 1`
 - meaning: Register 0 NOR Register 1. Store result in Register 2 

## I-Type Instructions
**ADDI**
The `addi` instruction adds values of register rs and imm, and stores the result in register rt
example:
`addi 2, 0, 52`
 - meaning: add values of register 0, and immediate value 52, store result in register 2

**SLTI**
The `slti` instruction checks if the value of register rs is less than the value imm. If true, register rt is set to 1, else set to 0
example:
`slti 2, 0, 10`
 - meaning: if value of register 0 is less than 10, set register 2 to value 1, else set register 2 to value 0.

**ANDI**
The `andi` instruction performs the bitwise AND operation on value in register rs and imm. The result is stored in register rt.
example:
`andi 2, 0, 36`
 - meaning: Register 0 AND value 36. Store result in Register 2 

**ORI**
The `ori` instruction performs the bitwise OR operation on value in register rs and imm. The result is stored in register rt.
example:
`ori 2, 0, 36`
 - meaning: Register 0 OR value 36. Store result in Register 2 

**XORI**
The `xori` instruction performs the bitwise XOR operation on value in register rs and imm. The result is stored in register rt.
example:
`xori 2, 0, 36`
 - meaning: Register 0 XOR value 36. Store result in Register 2 

## Branch Instructions

**BRANCH LESS THAN 0**
The `bltz` instruction checks if value of register rs is less than 0. If true, jump to label
example:
`bltz 1, exit`
 - meaning: If value of register 1 is less than 0, jump to 'exit', do nothing otherwise.

**BRANCH EQUAL**
The `beq` instruction checks if values of registers rs and rt are equal. If true, jump to label
example:
`beq 1, 2, exit`
 - meaning: If values of registers 1 and 2 are equal, jump to 'exit', do nothing otherwise

**BRANCH NOT EQUAL**
The `bne` instruction checks if values of registers rs and rt are not equal. If true, jump to label
example:
`bne 1, 2, exit`
 - meaning: If values of registers 1 and 2 are not equal, jump to 'exit', do nothing otherwise

## Jump Instructions

**JUMP**
The `j` instruction jumps to specified label
example:
`j exit`
 - meaning: jump to label 'exit'

**JUMP REGISTER**
The `jr` instruction jumps to value in register rs. In other words, Program Counter becomes the value from rs
example:
`j 3`
 - meaning: jump to value of register 3

**JUMP AND LINK**
The `jal` instruction jumps to specified label, and saves PC+1 in register 31
example:
`j exit`
 - meaning: jump to label 'exit', store value of PC+1 in register 31