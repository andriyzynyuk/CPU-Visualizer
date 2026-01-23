import { useState, useRef } from 'react';
import { useCpu } from '../cpu/CpuContext.jsx';
import SyntaxHighlighter from 'react-syntax-highlighter';
import { atomOneDark } from 'react-syntax-highlighter/dist/esm/styles/hljs';

function isPseudoInstruction(code) {
  const trimmed = code.trim().toLowerCase();
  if (trimmed === 'finish') return true;
  if (trimmed.match(/^output\s*\(?\s*\d+\s*\)?$/)) return true;
  return false;
}

function extractLabels(lines) {
  const labels = {};
  const codeLines = [];
  let instrIndex = 0;
  
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i];
    const trimmed = line.trim();
    
    if (!trimmed || trimmed.startsWith('#') || trimmed.startsWith(';')) {
      continue;
    }
    
    const labelMatch = trimmed.match(/^([a-zA-Z_][a-zA-Z0-9_]*):\s*(.*)$/);
    
    if (labelMatch) {
      const labelName = labelMatch[1].toLowerCase();
      const restOfLine = labelMatch[2].trim();
      
      if (labels.hasOwnProperty(labelName)) {
        return { error: `Line ${i + 1}: Duplicate label "${labelName}"` };
      }
      
      labels[labelName] = instrIndex;
      
      if (restOfLine && !restOfLine.startsWith('#') && !restOfLine.startsWith(';')) {
        codeLines.push({ lineNum: i + 1, code: restOfLine });
        if (!isPseudoInstruction(restOfLine)) {
          instrIndex++;
        }
      }
    } else {
      codeLines.push({ lineNum: i + 1, code: trimmed });
      if (!isPseudoInstruction(trimmed)) {
        instrIndex++;
      }
    }
  }
  
  return { labels, codeLines };
}

function calculateBranchOffset(currentIndex, targetIndex) {
  return targetIndex - currentIndex - 1;
}

function calculateJumpAddress(targetIndex) {
  return targetIndex;
}

function parseInstruction(code, instrLib, labels, currentIndex, lineNum) {
  const firstInstr = code.split(/\s{2,}|;|#/)[0];
  const trimmed = firstInstr.trim().toLowerCase();
  if (!trimmed) return null;
  
  const rTypeMatch = trimmed.match(/^(\w+)\s+(\d+)\s*,\s*(\d+)\s*,\s*(\d+)$/);
  if (rTypeMatch) {
    const [, instr, arg1, arg2, arg3] = rTypeMatch;
    const rd = parseInt(arg1, 10);
    const rs = parseInt(arg2, 10);
    const rt = parseInt(arg3, 10);
    
    switch (instr) {
      case 'add':
        return instrLib.instr_ADD(rd, rs, rt);
      case 'sub':
        return instrLib.instr_SUB(rd, rs, rt);
      case 'slt':
        return instrLib.instr_SLT(rd, rs, rt);
      case 'and':
        return instrLib.instr_AND(rd, rs, rt);
      case 'or':
        return instrLib.instr_OR(rd, rs, rt);
      case 'xor':
        return instrLib.instr_XOR(rd, rs, rt);
      case 'nor':
        return instrLib.instr_NOR(rd, rs, rt);
      default:
        break;
    }
  }
  
  const iTypeArithMatch = trimmed.match(/^(\w+)\s+(\d+)\s*,\s*(\d+)\s*,\s*(-?\d+)$/);
  if (iTypeArithMatch) {
    const [, instr, arg1, arg2, arg3] = iTypeArithMatch;
    const rt = parseInt(arg1, 10);
    const rs = parseInt(arg2, 10);
    const imm = parseInt(arg3, 10);
    
    switch (instr) {
      case 'addi':
        return instrLib.instr_ADDI(rt, rs, imm);
      case 'slti':
        return instrLib.instr_SLTI(rt, rs, imm);
      case 'andi':
        return instrLib.instr_ANDI(rt, rs, imm);
      case 'ori':
        return instrLib.instr_ORI(rt, rs, imm);
      case 'xori':
        return instrLib.instr_XORI(rt, rs, imm);
      default:
        break;
    }
  }
  
  const branchLabelMatch = trimmed.match(/^(beq|bne)\s+(\d+)\s*,\s*(\d+)\s*,\s*([a-zA-Z_][a-zA-Z0-9_]*)$/);
  if (branchLabelMatch) {
    const [, instr, arg1, arg2, labelName] = branchLabelMatch;
    const rs = parseInt(arg1, 10);
    const rt = parseInt(arg2, 10);
    const targetLabel = labelName.toLowerCase();
    
    if (!labels.hasOwnProperty(targetLabel)) {
      return { error: `Undefined label "${labelName}"` };
    }
    
    const targetIndex = labels[targetLabel];
    const offset = calculateBranchOffset(currentIndex, targetIndex);
    
    switch (instr) {
      case 'beq':
        return instrLib.instr_BEQ(rs, rt, offset);
      case 'bne':
        return instrLib.instr_BNE(rs, rt, offset);
      default:
        break;
    }
  }
  
  const branchImmMatch = trimmed.match(/^(beq|bne)\s+(\d+)\s*,\s*(\d+)\s*,\s*(-?\d+)$/);
  if (branchImmMatch) {
    const [, instr, arg1, arg2, arg3] = branchImmMatch;
    const rs = parseInt(arg1, 10);
    const rt = parseInt(arg2, 10);
    const offset = parseInt(arg3, 10);
    
    switch (instr) {
      case 'beq':
        return instrLib.instr_BEQ(rs, rt, offset);
      case 'bne':
        return instrLib.instr_BNE(rs, rt, offset);
      default:
        break;
    }
  }
  
  const bltzLabelMatch = trimmed.match(/^bltz\s+(\d+)\s*,\s*([a-zA-Z_][a-zA-Z0-9_]*)$/);
  if (bltzLabelMatch) {
    const [, arg1, labelName] = bltzLabelMatch;
    const rs = parseInt(arg1, 10);
    const targetLabel = labelName.toLowerCase();
    
    if (!labels.hasOwnProperty(targetLabel)) {
      return { error: `Undefined label "${labelName}"` };
    }
    
    const targetIndex = labels[targetLabel];
    const offset = calculateBranchOffset(currentIndex, targetIndex);
    return instrLib.instr_BLTZ(rs, offset);
  }
  
  const bltzImmMatch = trimmed.match(/^bltz\s+(\d+)\s*,\s*(-?\d+)$/);
  if (bltzImmMatch) {
    const [, arg1, arg2] = bltzImmMatch;
    const rs = parseInt(arg1, 10);
    const offset = parseInt(arg2, 10);
    return instrLib.instr_BLTZ(rs, offset);
  }
  
  const jrMatch = trimmed.match(/^jr\s+(\d+)$/);
  if (jrMatch) {
    const rs = parseInt(jrMatch[1], 10);
    return instrLib.instr_JR(rs);
  }
  
  const jTypeLabelMatch = trimmed.match(/^(j|jal)\s+([a-zA-Z_][a-zA-Z0-9_]*)$/);
  if (jTypeLabelMatch) {
    const [, instr, labelName] = jTypeLabelMatch;
    const targetLabel = labelName.toLowerCase();
    
    if (!labels.hasOwnProperty(targetLabel)) {
      return { error: `Undefined label "${labelName}"` };
    }
    
    const targetIndex = labels[targetLabel];
    const jumpAddr = calculateJumpAddress(targetIndex);
    
    switch (instr) {
      case 'j':
        return instrLib.instr_JUMP(jumpAddr);
      case 'jal':
        return instrLib.instr_JAL(jumpAddr);
      default:
        break;
    }
  }
  
  const jTypeImmMatch = trimmed.match(/^(j|jal)\s+(\d+)$/);
  if (jTypeImmMatch) {
    const [, instr, arg1] = jTypeImmMatch;
    const jumpAddr = parseInt(arg1, 10);
    
    switch (instr) {
      case 'j':
        return instrLib.instr_JUMP(jumpAddr);
      case 'jal':
        return instrLib.instr_JAL(jumpAddr);
      default:
        break;
    }
  }
  
  return { error: 'Invalid instruction format' };
}

function parseCode(codeText, instrLib) {
  const lines = codeText.split('\n');
  
  const labelResult = extractLabels(lines);
  if (labelResult.error) {
    return { error: labelResult.error };
  }
  
  const { labels, codeLines } = labelResult;
  
  if (codeLines.length === 0) {
    return { error: "No valid instructions found" };
  }
  
  const instructions = [];
  const instructionTexts = [];
  let finishIndex = -1;
  const outputInstructions = [];
  
  for (let i = 0; i < codeLines.length; i++) {
    const { lineNum, code } = codeLines[i];
    
    const finishMatch = code.trim().toLowerCase().match(/^finish$/);
    if (finishMatch) {
      if (finishIndex !== -1) {
        return { error: `Line ${lineNum}: Multiple 'finish' instructions not allowed` };
      }
      finishIndex = instructions.length;
      continue;
    }
    
    const outputMatch = code.trim().toLowerCase().match(/^output\s*\(?\s*(\d+)\s*\)?$/);
    if (outputMatch) {
      const register = parseInt(outputMatch[1], 10);
      if (register < 0 || register > 31) {
        return { error: `Line ${lineNum}: Invalid register number ${register} (must be 0-31)` };
      }
      outputInstructions.push({ instrIndex: instructions.length, register, lineNum });
      continue;
    }

    const currentInstrIndex = instructions.length;
    const result = parseInstruction(code, instrLib, labels, currentInstrIndex, lineNum);
    
    if (result && result.error) {
      return { error: `Line ${lineNum}: ${result.error}` };
    } else if (result !== null) {
      instructions.push(result);
      instructionTexts.push(code.trim());
    }
  }
  
  return { instructions, instructionTexts, labels, finishIndex, outputInstructions };
}

const EXAMPLE_CODE =`
# Example Program
# Calculates the sum of 1 to 5

# Initialize registers
addi 1, 0, 5       # reg1 = 5 (counter)
addi 2, 0, 0       # reg2 = 0 (sum)

loop:
    add 2, 2, 1    # sum = sum + counter
    addi 1, 1, -1  # counter = counter - 1
    bne 1, 0, loop # if counter != 0, continue loop

# Output the result
output(2)

finish
`;

export default function CodeEditor({ menuOpen, onShowHelp }) {
  const [codeDraft, setCodeDraft] = useState("");
  const [error, setError] = useState("");
  const { instrLib, loadInstructions, ready, outputs } = useCpu();
  const textareaRef = useRef(null);
  const highlighterRef = useRef(null);

  const handleResetCode = () => {
    setCodeDraft("");
    setError("");
  };

  const loadExampleCode = () => {
    setCodeDraft(EXAMPLE_CODE);
    setError("");
  };

  const handleScroll = (e) => {
    if (highlighterRef.current) {
      highlighterRef.current.scrollTop = e.target.scrollTop;
    }
  };
  
  const handleExecuteCode = () => {
    if (!ready || !instrLib) {
      setError("CPU not ready yet");
      return;
    }
    
    const result = parseCode(codeDraft, instrLib);
    
    if (result.error) {
      setError(result.error);
      return;
    }
    
    const { instructions, instructionTexts, labels, finishIndex, outputInstructions } = result;
    
    if (instructions.length === 0) {
      setError("No valid instructions found");
      return;
    }
    
    if (finishIndex === -1) {
      setError("Missing 'finish' instruction - add 'finish' at the end of your code");
      return;
    }
    
    setError("");
    loadInstructions(instructions, { finishIndex, outputInstructions, instructionTexts });
    
    const labelCount = Object.keys(labels).length;
    const labelInfo = labelCount > 0 
      ? ` (${labelCount} label${labelCount > 1 ? 's' : ''}: ${Object.keys(labels).join(', ')})`
      : '';
    const finishInfo = finishIndex !== -1 ? `, finish at instruction ${finishIndex}` : '';
    const outputInfo = outputInstructions.length > 0 ? `, ${outputInstructions.length} output(s)` : '';
    console.info(`Loaded ${instructions.length} instruction(s)${labelInfo}${finishInfo}${outputInfo}, CPU reset to cycle 0`);
  };

  return (
    <nav className={`side-menu ${menuOpen ? 'open' : ''}`}>
      <div className="side-menu__section">
        <div className="side-menu__header">
          <span className="side-menu__title">Code Editor</span>
          <div className="side-menu__header-actions">
            <button
              className="side-menu__icon-btn"
              onClick={loadExampleCode}
              title="Load example code"
              aria-label="Load example code"
            >
              Load Example
            </button>
            <button
              className="side-menu__icon-btn"
              onClick={onShowHelp}
              title="Programming help"
              aria-label="Programming help"
            >
              Help
            </button>
          </div>
        </div>
        <div className="code-editor-container">
          <div className="side-menu__highlighter" ref={highlighterRef}>
            <SyntaxHighlighter
              language="asm"
              style={atomOneDark}
              showLineNumbers={false}
              wrapLines={true}
              wrapLongLines={true}
              customStyle={{
                margin: 0,
                padding: 0,
                background: 'transparent',
                overflow: 'visible'
              }}
              codeTagProps={{
                style: {
                  whiteSpace: 'pre-wrap',
                  wordBreak: 'break-all'
                }
              }}
            >
              {codeDraft || ' '}
            </SyntaxHighlighter>
          </div>
          <textarea
            ref={textareaRef}
            className="side-menu__textarea"
            placeholder="Enter instructions"
            value={codeDraft}
            onChange={(e) => setCodeDraft(e.target.value)}
            onScroll={handleScroll}
            spellCheck="false"
          />
        </div>
        {error && (
          <div className="code-editor__error">
            {error}
          </div>
        )}
        {outputs && outputs.length > 0 && (
          <div className="code-editor__outputs">
            {outputs.map((out, idx) => (
              <div key={idx} className="code-editor__output">
                Output (r{out.register}): {out.value}
              </div>
            ))}
          </div>
        )}
        <div className="side-menu__actions">
          <button className="side-menu__btn ghost" onClick={handleResetCode}>
            Reset
          </button>
          <button className="side-menu__btn solid" onClick={handleExecuteCode}>
            Execute
          </button>
        </div>
      </div>
    </nav>
  );
}
