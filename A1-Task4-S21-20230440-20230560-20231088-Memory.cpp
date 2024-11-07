// Memory.cpp

#include "A1-Task4-S21-20230440-20230560-20231088-Memory.h"
#include <stdexcept>

// memory constructor
Memory::Memory() : memory(256, "00") {} // Initialize memory with 256 cells set to "00"

// getting the cell of the memory
string Memory::getCell(int address) {
    if (address < 0 || address >= memory.size()) {
        throw out_of_range("Memory address out of range.");
    }
    return memory[address];
}

// setting the cell of the memory
void Memory::setCell(int address, const string& value) {
    if (address < 0 || address >= memory.size()) {
        throw out_of_range("Memory address out of range.");
    }
    memory[address] = value;
}

// function to print the memory matrix
void Memory::printMemory(){
    // the matrix will have 16 rows and 16 columns
    int col = 16;
    // printing the matrix
    cout << "\n---------------------> The Memory matrix <---------------------\n";
    for (int i = 0; i < 256; i++) {
        if (i % col == 0 && i != 0) {
            cout << endl;  // Move to the next row once the column 16 is reached
        }
        // Print each memory cell
        cout << getCell(i) << "  ";
    }
    cout << endl;
}
