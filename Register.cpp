#include "Register.h"
#include "CPU.h"

// register constructor, setting all the register to 0 when initializing,
Register::Register() : registers(16, "00") {
    counter = nullptr;
}

// get function to get a specific cell of the register
string Register::get_Cell(int index) const{
    if (index >= 0 && index < 16) {
        return registers[index]; // Return the value at the specified index
    }
    else {
        return "00";// Return "00" for invalid index
    }
}

// set cell function for the register
void Register::set_cell(int index, const std::string& value) {
    if (index >= 0 && index < 16) {
        string formattedValue;
        // Ensure the value is two characters
        if (value.length() < 2) {
            formattedValue = "0" + value;
        } else if (value.length() > 2) {
            formattedValue = value.substr(value.length() - 2, 2);
        } else {
            formattedValue = value;
        }
        registers[index] = formattedValue;

        // Debug output to verify the set operation
        cout << "Setting register " << index << " to value: " << formattedValue << endl;
    } else {
        cout << "Invalid register index: " << index << endl;
    }
}
void Register::printRegister() {
    cout << "----------------------------------------\n";
    cout << "\nRegisters:\n";
    for (int i = 0; i < 16; ++i) {
        cout << "R" << i << ": " << get_Cell(i) << "\n";
    }

}
// getting program counter
CPU* Register::get_PC() const {
    return counter;
}

// setting program counter
void Register::set_PC(int address) {
    counter = reinterpret_cast<CPU *>(address);
}