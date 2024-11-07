// CU.cpp
#include "A1-Task4-S21-20230440-20230560-20231088-CU.h"
#include <iostream>
#include "A1-Task4-S21-20230440-20230560-20231088-MainUI.h"
#include "A1-Task4-S21-20230440-20230560-20231088-Register.h"

// load function
void CU::load(int reg, int address, Memory& memory, Register& registers) {
    registers.set_cell(reg, memory.getCell(address));
}

// load register function
void CU::loadImmediate(int reg, const string& value, Register& registers) {
    // Load immediate value to register
    registers.set_cell(reg, value);
}
// store function
void CU::store(int reg, int address, Memory& memory, Register& registers) {
    registers.set_cell(address, registers.get_Cell(reg));
}

// store to output function
void CU::storeToOutput(int reg,Register&registers) {
    cout << "Output: " << registers.get_Cell(reg) << endl;
}

// move function
void CU::move(int regS, int regT, Register& registers) {
    registers.set_cell(regT, registers.get_Cell(regS));
}

// jump function
void CU::jump(int reg, int address, Memory& memory, Register& registers) {
    if (registers.get_Cell(reg) == memory.getCell(address)) {
        // Jump to specified location if condition met
        registers.set_PC(address);
    }
}

void CU::halt() {
    std::cout << "Program execution halted."<<endl;
}