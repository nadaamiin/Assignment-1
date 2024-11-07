#ifndef VOLEMACHINE_CPU_H
#define VOLEMACHINE_CPU_H
#pragma once
#include <string>
#include <vector>
#include "Memory.h"
#include "Register.h"
#include "ALU.h"
#include "CU.h"

using namespace std;
class Register;
class ALU;
class CU;

// CPU class
class CPU {
private:
    // declaring the members of the class
    int counter;
    string instructionReg;
    Register& registers;
    ALU* alu;
    CU* cu;
    Memory memo;

public:
    // the functions of the class
    CPU(Register& reg);
    void runNextInstruction(Memory& memory);
    void fetch(Memory& memory);
    vector<string> decode(const string& instructionReg);
    void execute(vector<string>& decoded, Memory& memory);
    void displayState();
    bool hasInstructionsToRun(Memory& memory) const;
    int getCounter() const {
        return counter;
    }
};

#endif // VOLEMACHINE_CPU_H