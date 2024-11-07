#ifndef VOLEMACHINE_MAINUI_H
#define VOLEMACHINE_MAINUI_H

#include <iostream>
#include <fstream>
#include <vector>
#include "string"
#include "Memory.h"
#include "Register.h"

using namespace std;

class MainUI {
private:
    fstream file; // Member variable to handle file operations

public:
    MainUI(); // Constructor declaration
    // vector to store the operations that will be done
    vector<string> operations;

    void DisplayMenu();
    string getinstruction(int address);
    // input file
    string inputFileName();
    // loading from the input file
    void loadFromFile(Memory& memory);

};

#endif // VOLEMACHINE_MAINUI_H
