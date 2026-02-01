
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

---

## Shifting Instructions

| Instruction | Description                                 | Format           |
|------------|----------------------------------------------|------------------|
| `SLL`      | Shift Left Logical                           | `sll rd, rt, sh` |
| `SRL`      | Shift Right Logical                          | `srl rd, rt, sh` |
| `SRA`      | Shift Right Arithmetic                       | `sra rd, rt, sh` |
| `SLLV`     | Shift Left Logical Variable                  | `sllv rd, rt, rs`|
| `SRLV`     | Shift Right Lorigcal Variable                | `srlv rd, rt, rs`|
| `SRAV`     | Shift Right Arithmetic Variable              | `srav rd, rt, rs`|

---

## In-Depth

Here you will find detailed information about each Instruction available to use.

## System Instructions

**Finish**

The `finish` instruction marks where program execution ends. It must be written at least once in your program.

Example:

`finish`

- Meaning: When the Program Counter reaches 'finish', program execution will end.

**Output**

The `output` instruction displays the value of a specified register. This instruction has no influence on the CPU and is solely used for convenience.

Example:

`output(26)`

- Meaning: Displays the value of register 26.

## R-Type Instructions

**ADD**

The `add` instruction adds the values of registers rs and rt, and stores the result in register rd.

Example:

`add 2, 0, 1`

- Meaning: Add the values of registers 0 and 1, then store the result in register 2.

**SUB**

The `sub` instruction subtracts the value of register rt from register rs, and stores the result in register rd.

Example:

`sub 2, 0, 1`

- Meaning: Subtract the value of register 1 from register 0, then store the result in register 2.

**SLT**

The `slt` instruction checks if the value of register rs is less than the value of register rt. If true, register rd is set to 1; otherwise, it is set to 0.

Example:

`slt 2, 0, 1`

- Meaning: If the value of register 0 is less than register 1, set register 2 to 1; otherwise, set it to 0.

**AND**

The `and` instruction performs a bitwise AND operation on the values in registers rs and rt. The result is stored in register rd.

Example:

`and 2, 0, 1`

- Meaning: Perform a bitwise AND on registers 0 and 1, then store the result in register 2.

**OR**

The `or` instruction performs a bitwise OR operation on the values in registers rs and rt. The result is stored in register rd.

Example:

`or 2, 0, 1`

- Meaning: Perform a bitwise OR on registers 0 and 1, then store the result in register 2.

**XOR**

The `xor` instruction performs a bitwise XOR operation on the values in registers rs and rt. The result is stored in register rd.

Example:

`xor 2, 0, 1`

- Meaning: Perform a bitwise XOR on registers 0 and 1, then store the result in register 2.

**NOR**

The `nor` instruction performs a bitwise NOR operation on the values in registers rs and rt. The result is stored in register rd.

Example:

`nor 2, 0, 1`

- Meaning: Perform a bitwise NOR on registers 0 and 1, then store the result in register 2. 

## I-Type Instructions

**ADDI**

The `addi` instruction adds the value of register rs and the immediate value imm, then stores the result in register rt.

Example:

`addi 2, 0, 52`

- Meaning: Add register 0 and the immediate value 52, then store the result in register 2.

**SLTI**

The `slti` instruction checks if the value of register rs is less than the immediate value imm. If true, register rt is set to 1; otherwise, it is set to 0.

Example:

`slti 2, 0, 10`

- Meaning: If the value of register 0 is less than 10, set register 2 to 1; otherwise, set it to 0.

**ANDI**

The `andi` instruction performs a bitwise AND operation on the value in register rs and the immediate value imm. The result is stored in register rt.

Example:

`andi 2, 0, 36`

- Meaning: Perform a bitwise AND on register 0 and the value 36, then store the result in register 2.

**ORI**

The `ori` instruction performs a bitwise OR operation on the value in register rs and the immediate value imm. The result is stored in register rt.

Example:

`ori 2, 0, 36`

- Meaning: Perform a bitwise OR on register 0 and the value 36, then store the result in register 2.

**XORI**

The `xori` instruction performs a bitwise XOR operation on the value in register rs and the immediate value imm. The result is stored in register rt.

Example:

`xori 2, 0, 36`

- Meaning: Perform a bitwise XOR on register 0 and the value 36, then store the result in register 2. 

## Branch Instructions

**BRANCH LESS THAN 0**

The `bltz` instruction checks if the value of register rs is less than 0. If true, the program jumps to the specified label.

Example:

`bltz 1, exit`

- Meaning: If the value of register 1 is less than 0, jump to the 'exit' label; otherwise, continue.

**BRANCH EQUAL**

The `beq` instruction checks if the values of registers rs and rt are equal. If true, the program jumps to the specified label.

Example:

`beq 1, 2, exit`

- Meaning: If the values of registers 1 and 2 are equal, jump to the 'exit' label; otherwise, continue.

**BRANCH NOT EQUAL**

The `bne` instruction checks if the values of registers rs and rt are not equal. If true, the program jumps to the specified label.

Example:

`bne 1, 2, exit`

- Meaning: If the values of registers 1 and 2 are not equal, jump to the 'exit' label; otherwise, continue.

## Jump Instructions

**JUMP**

The `j` instruction jumps to the specified label.

Example:

`j exit`

- Meaning: Jump to the 'exit' label.

**JUMP REGISTER**

The `jr` instruction jumps to the address stored in register rs. In other words, the Program Counter becomes the value from rs.

Example:

`jr 3`

- Meaning: Jump to the address stored in register 3.

**JUMP AND LINK**

The `jal` instruction jumps to the specified label and saves the return address (PC+4) in register 31.

Example:

`jal exit`

- Meaning: Jump to the 'exit' label and store the return address in register 31.


## Shift Instructions

**Shift Left Logical**

The `sll` instruction shifts the value of register rt to the left by sh positions, storing the result in register rd.

Example:

`sll 1, 0, 1`

- Meaning: Shift register 0 left by 1 position. If register 0 = 1110, result = 11100.

**Shift Right Logical**

The `srl` instruction shifts the value of register rt to the right by sh positions, storing the result in register rd.

Example:

`srl 1, 0, 1`

- Meaning: Shift register 0 right by 1 position. If register 0 = 1110, result = 111.

**Shift Right Arithmetic**

The `sra` instruction shifts the value of register rt to the right by sh positions, storing the result in register rd. Arithmetic shifting preserves the sign of the original value.

Example:

`sra 1, 0, 1`

- Meaning: Shift register 0 right by 1 position. If register 0 = -6, result = -3.

**Shift Left Logical Variable**

The `sllv` instruction shifts the value of register rt to the left. The shift amount is determined by the lower 5 bits of register rs. The result is stored in register rd.

Example:

`sllv 1, 0, 3`

- Meaning: Shift register 0 left by the amount specified in the lower 5 bits of register 3.

**Shift Right Logical Variable**

The `srlv` instruction shifts the value of register rt to the right. The shift amount is determined by the lower 5 bits of register rs. The result is stored in register rd.

Example:

`srlv 1, 0, 3`

- Meaning: Shift register 0 right by the amount specified in the lower 5 bits of register 3.

**Shift Right Arithmetic Variable**

The `srav` instruction shifts the value of register rt to the right. The shift amount is determined by the lower 5 bits of register rs. The result is stored in register rd. Arithmetic shifting preserves the sign of the original value.

Example:

`srav 1, 0, 3`

- Meaning: Shift register 0 right by the amount specified in the lower 5 bits of register 3.