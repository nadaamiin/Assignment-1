#include "A1-Task4-S21-20230440-20230560-20231088-ALU.h"
#include <bitset>
#include <sstream>
#include "iostream"
#include "A1-Task4-S21-20230440-20230560-20231088-Register.h"
#include "cmath"
#include "cstring"

using namespace std;

// conversion hex to dec
int ALU::hex_to_dec(const string& h) {
    return static_cast<int>(stoul(h, nullptr, 16));
}

// conversion hex to bin
bitset<8> ALU::hex_to_bin(const string& h) {
    int dec = hex_to_dec(h);
    return bitset<8>(dec);
}

// conversion dec to bin
bitset<8> ALU::dec_to_bin(int d) {
    return bitset<8>(d);
}

// conversion dec to hex
string ALU::dec_to_hex(int d) {
    stringstream ss;
    ss << uppercase << hex << d;
    return ss.str();
}

// conversion bin to dec
int ALU::bin_to_dec(const string& b) {
    return static_cast<int>(bitset<32>(b).to_ullong());
}

// conversion bin to hex
string ALU::bin_to_hex(const string& b) {
    int d = bin_to_dec(b);
    return dec_to_hex(d);
}

// addition function (2's complement)
void ALU::add(int val1, int val2, int resultReg, Register& registers) {
    // Get values from the registers based on the provided indices
    string regVal1 = registers.get_Cell(val1); // Get value from register 1
    string regVal2 = registers.get_Cell(val2); // Get value from register 2

    // Convert to decimal to perform addition
    int num1 = hex_to_dec(regVal1);
    int num2 = hex_to_dec(regVal2);

    // Perform the addition
    int sum = num1 + num2;

    // Store the result in the specified result register
    registers.set_cell(resultReg, dec_to_hex(sum)); // Store result in result register
}

// addition function (floating point)
void ALU::addFloatingPoint(int destReg, int srcReg1, int srcReg2, Register& registers) {
    // Get values from the registers based on the provided indices
    string regVal1 = registers.get_Cell(srcReg1);
    string regVal2 = registers.get_Cell(srcReg2);

    // Convert hex to float using IEEE 754
    float float1, float2;
    unsigned int intVal1 = hex_to_dec(regVal1);
    unsigned int intVal2 = hex_to_dec(regVal2);

    // Use memcpy to convert the integer representation to float
    memcpy(&float1, &intVal1, sizeof(float));
    memcpy(&float2, &intVal2, sizeof(float));

    // Perform the floating-point addition
    float result = float1 + float2;

    // Convert the result back to hexadecimal
    unsigned int intResult;
    memcpy(&intResult, &result, sizeof(float));

    // Store the result in the specified register
    registers.set_cell(destReg, dec_to_hex(intResult));
}
