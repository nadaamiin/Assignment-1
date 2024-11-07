// MainUI.cpp
#include "A1-Task4-S21-20230440-20230560-20231088-MainUI.h"
#include "A1-Task4-S21-20230440-20230560-20231088-Memory.h"
#include <sstream>
#include <stdexcept>

MainUI::MainUI() {
    // Initialize file or any other member variables if needed
}

// taking the input file from the user
string MainUI::inputFileName() {
    string filename;
    cout << "--> Please enter the file name to be used in the Vole machine: \n";
    // validation check to make sure that the file is open and in the right format
    while (true) {
        cin >> filename;
        file.open(filename, ios::in);
        if (!file.is_open()) {
            cout << "\nError opening file! Please enter a valid file name.\n";
            file.clear();
            continue;
        } else {
            break;
        }
    }
    return filename;
}


string MainUI::getinstruction(int address) {
    return operations[address];
}

// loading from the input file, by storing the instructions into the machine
void MainUI::loadFromFile(Memory& memory) {
    std::string filename = inputFileName(); // Get filename from user

    // Clear the operations vector in case of multiple loads
    operations.clear();

    // Reset file to start reading
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string file_line, word;

    // Read each line from the file and split into words
    while (std::getline(file, file_line)) {
        std::istringstream stream1(file_line);
        while (stream1 >> word) {
            // If the instruction starts with "0x" or "0X", remove it
            if (word.size() >= 4 && (word[0] == '0' && (word[1] == 'x' || word[1] == 'X'))) {
                word = word.substr(2);
            }

            // Split the word into two-character parts and load each part as an instruction
            for (size_t i = 0; i < word.size(); i += 2) {
                if (i + 2 <= word.size()) {
                    operations.push_back(word.substr(i, 2)); // Take two characters at a time
                }
            }
        }
    }    // Load operations into memory cells
    for (int i = 0; i < operations.size() && i < 256; i++) {
        memory.setCell(i, operations[i]);
    }
    file.close(); // Close the file after loading

}