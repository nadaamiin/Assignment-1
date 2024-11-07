#ifndef VOLEMACHINE_CU_H
#define VOLEMACHINE_CU_H
#pragma once

#include <string>
#include "A1-Task4-S21-20230440-20230560-20231088-Register.h"
#include "A1-Task4-S21-20230440-20230560-20231088-Memory.h"
#include "A1-Task4-S21-20230440-20230560-20231088-ALU.h"
#include "A1-Task4-S21-20230440-20230560-20231088-MainUI.h"

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