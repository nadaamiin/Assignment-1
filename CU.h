#ifndef VOLEMACHINE_CU_H
#define VOLEMACHINE_CU_H
#pragma once

#include <string>
#include "Register.h"
#include "Memory.h"
#include "ALU.h"
#include "MainUI.h"

class CU {
public:
    // constructor
    CU(){}

    // load function
    void load(int reg, int address, Memory& memory, Register& registers);  // Opcode 1

    // load register to register
    void loadImmediate(int reg, const string& value, Register& registers); // Opcode 2

    // store function
    void store(int reg, int address, Memory& memory, Register& registers);  // Opcode 3

    // store to output to the screen
    void storeToOutput(int reg,Register&registers);                        // Opcode 3 with R00

    // move the bit pattern from register to register
    void move(int regS, int regT, Register& registers);                    // Opcode 4

    // jump operation
    void jump(int reg, int address, Memory& memory, Register& registers);  // Opcode B

    // halt --> exit
    void halt();                                                           // Opcode C
};

#endif // end CU_H