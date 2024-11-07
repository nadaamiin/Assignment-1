#include "CPU.h"
#include "CU.h"
#include "Register.h"
#include "Memory.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// CPU constructor
CPU::CPU(Register& reg) : registers(reg), counter(0), cu(), alu(), memo() {
    instructionReg = memo.getCell(counter);
}

// Running next instruction
void CPU::runNextInstruction(Memory& memory) {
    cout << "Current counter: " << counter << endl;
    fetch(memory);
    vector<string> decoded = decode(instructionReg);
    execute(decoded, memory);
    counter += 2;  // Increment counter after instruction execution
}

// Displaying the state of the constructor
void CPU::displayState() {
    cout << "----------------------------------------\n";
    cout << "\nRegisters:\n";
    for (int i = 0; i < 16; ++i) {
        cout << "R" << i << ": " << registers.get_Cell(i) << "\n";
    }
}

// Checking if there are instructions to run
bool CPU::hasInstructionsToRun(Memory& memory) const {
    if (counter >= memory.getSize()) {
        return false;
    }
    return memory.getCell(counter) != "00";
}

// Fetching the next instruction
void CPU::fetch(Memory& memory) {
    if (counter >= memory.getSize()) {
        throw runtime_error("Program counter out of bounds");
    }
    instructionReg = memory.getCell(counter);
}

// Decoding the instruction
vector<string> CPU::decode(const string& instructionReg) {
    vector<string> decoded_instructions;

    if (instructionReg.empty()) {
        throw runtime_error("Empty instruction encountered");
    }

    // Convert to uppercase to handle both cases
    char firstChar = toupper(instructionReg[0]);
    decoded_instructions.push_back(string(1, firstChar));

    if (instructionReg.length() > 1) {
        decoded_instructions.push_back(instructionReg.substr(1));
    }

    cout << "Decoded opcode: " << firstChar << endl;
    return decoded_instructions;
}

// Executing the instruction
void CPU::execute(vector<string>& decoded, Memory& memory) {
    if (decoded.empty()) {
        throw runtime_error("No instruction to execute.");
    }

    char opCode = decoded[0][0];  // Opcode already in uppercase from decode

    // Validate opcode before execution
    string validOpcodes = "123456BC";
    if (validOpcodes.find(opCode) == string::npos) {
        throw runtime_error("Invalid opcode: " + string(1, opCode));
    }

    try {
        switch (opCode) {
            case '1': { // Load
                int reg = decoded[1][0] - '0';
                int address = decoded[1][1] - '0';
                if (address < 0 || address >= memory.getSize()) {
                    throw runtime_error("Memory address out of range.");
                }
                cu->load(reg, address, memory, registers);
                cout << "load\n";
                break;
            }
            case '2': { // Load Immediate
                int reg = decoded[1][0] - '0';
                string value = decoded[1].substr(1);
                cu->loadImmediate(reg, value, registers);
                break;
            }
            case '3': { // Store
                cout << "store\n";
                int reg = decoded[1][0] - '0';
                if (reg < 0 || reg > 15) {
                    throw runtime_error("Invalid register index in store instruction");
                }
                string value = registers.get_Cell(reg);
                memory.setCell(counter, value);
                cu->store(reg, counter, memory, registers);
                break;
            }
            case '4': { // Move
                // Parse the destination and current registers from the instruction
                int destination = decoded[1][0] - '0';
                int source = decoded[1][1] - '0';

                // Perform the move operation
                cu->move(source, destination, registers);
                break;
            }
            case '5': { // Add
                int destReg = decoded[1][0] - '0';
                int srcReg1 = decoded[1][1] - '0';
                int srcReg2 = decoded[1][2] - '0';
                alu->add(srcReg1, srcReg2, destReg, registers);
                break;
            }
            case '6': { // Floating point add
                if (decoded[1].length() < 3) {
                    throw runtime_error("Invalid floating point add instruction format");
                }
                int destReg = decoded[1][0] - '0';
                int srcReg1 = decoded[1][1] - '0';
                int srcReg2 = decoded[1][2] - '0';
                if (destReg < 0 || destReg > 15 || srcReg1 < 0 || srcReg1 > 15 ||
                    srcReg2 < 0 || srcReg2 > 15) {
                    throw runtime_error("Invalid register index in floating point add");
                }
                alu->addFloatingPoint(destReg, srcReg1, srcReg2, registers);
                break;
            }
            case 'B': { // Jump
//                int reg = decoded[1][0] - '0';
//                int address = alu->hex_to_dec(decoded[1].substr(1));
//                cu->jump(reg, address, memory, registers);
                break;
            }
            case 'C': // Halt

                break;
            default:
                throw runtime_error("Unknown opcode: " + string(1, opCode));
        }
    } catch (const exception& e) {
        cerr << "Error executing instruction at counter " << counter << ": "
             << e.what() << endl;
        throw;
    }
}
