#ifndef VOLEMACHINE_REGISTER_H
#define VOLEMACHINE_REGISTER_H

#include <iostream>
#include <vector>

using namespace std;
class CPU;
// Register class
class Register {
private:
    // vector for the registers
    vector <string>registers{16,"00"};
    CPU* counter;
public:
    // register constructor
    Register();
    // getting the cell value of a specific index in a register
    string get_Cell(int index) const;
    // setting the register with a specific value at a specific index
    void set_cell(int index, const string& value);
    void printRegister();
    CPU * get_PC() const; // Getter for the Program Counter
    void set_PC(int address); // Setter for the program counter
};

#endif // VOLEMACHINE_REGISTER_H
