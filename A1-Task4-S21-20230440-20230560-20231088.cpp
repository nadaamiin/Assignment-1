// File: A1-Task4-S21-20230440-20230560-20231088.cpp
// Purpose: Vole machine program
// Author: Nourhan Mohammed Ahmed Fahmy, Nada Amin Fawzy, Safia Mohammed Saied
// Section: 21
// ID: (Nourhan - 20230560)(Nada - 20230440)(Safia - 20231088)
// Date: 7 Nov 2024

// main.cpp

#include "MainUI.h"
#include "Memory.h"
#include "Register.h"
#include "CPU.h"

// display the meaning of the instructions
void displayinstructions(){
    cout << "\nThe instruction details:\n[1 RXY] LOAD the register R with the bit pattern found in the memory cell whose address is XY\n"
            "[2 RXY] Load the register R with the bit pattern XY\n"
            "[3 RXY] STORE the bit pattern found in register R with the bit pattern XY\n"
            "[3 R00] STORE to location 00, writing to the screen"
            "[4 ORS] MOVE the bit pattern found in register R to register S\n"
            "[5 RST] ADD the bit patterns in registers S and T (2's complement addition)\n"
            "[6 RST] ADD the bit pattern in registers S and T (floating point notation)\n"
            "[B RXY] JUMP to the instruction located in the memory cell at address XY\n"
            "[C OOO] HALT execution\n";
}

int main() {
    Register registers;
    Memory memory;
    MainUI ui;
    CPU cpu(registers);

    int choice;
    cout << "***** Welcome to the Vole machine program *****\n";
    while(true) {
        // asking the user what he wants to do
        cout << "\nWhat would you like to do?\n"
                "1) Load a new program from a file\n2) Display the instruction information\n3) Display program counter\n4) Exit\n";
        while (true) {
            // validation check to make sure a valid choice was input
            cin >> choice;
            if (cin.fail() || choice <= 0 || choice > 5) {
                // Clear n input
                cin.clear();
                // Ignore n input
                cin.ignore(1000, '\n');
                cout << "\nInvalid input!! Please enter a suitable choice\n";
                continue;
            }
            break;
        }

        // the user wants to load a new program from the file
        if (choice == 1) {
            // load the instructions from the file into the memory vector
            ui.loadFromFile(memory);
            //CPU cpu(registers);
            memory.printMemory();

            try {
                while (cpu.hasInstructionsToRun(memory)) {
                    cpu.runNextInstruction(memory);
                }
            } catch (const std::exception& e) {
                cout << "Runtime error: " << e.what() << endl;
            }

            // display the final state of the register after all instructions are executed
            cpu.displayState();
            continue;

            // the user wants to display the details of the instructions
        } else if (choice == 2) {
            displayinstructions();
            continue;

            // the user wants to output the program counter
        } else if (choice == 3) {
            cout << "The program counter is: " << cpu.getCounter() << endl;
            continue;

            // the user wants to exit
        } else if (choice == 4) {
            cout << "***  Thank you for using the Vole machine program  ***\n";
            break;
        }
    }
    return 0;
}
