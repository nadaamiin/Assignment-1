#ifndef VOLEMACHINE_ALU_H
#define VOLEMACHINE_ALU_H
#pragma once

#include <bitset>
#include <sstream>
#include <string>
#include "Register.h"
#include "CPU.h"

using namespace std;

class ALU {
private:

public:
    // the functions in the ALU.cpp

    int hex_to_dec(const string& h);
    bitset<8> hex_to_bin(const string& h);
    bitset<8> dec_to_bin(int d);
    string dec_to_hex(int d);
    int bin_to_dec(const string& b);
    string bin_to_hex(const string& b);
    void add(int val1, int val2, int resultReg, Register &registers);
    void addFloatingPoint(int destReg, int srcReg1, int srcReg2, Register& registers);

};

#endif // VOLEMACHINE_ALU_H
