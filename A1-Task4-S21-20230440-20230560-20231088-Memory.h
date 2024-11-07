#ifndef VOLEMACHINE_MEMORY_H
#define VOLEMACHINE_MEMORY_H

#include <iostream>
#include <vector>

using namespace std;

class Memory {
private:
    // vector of memory
    vector<string> memory{256, "00"};

public:
    // memory constructor
    Memory();
    // getting the value at a specific in the memory
    string getCell(int address);
    // setting the memory with a specific value at a specific index
    void setCell(int address, const string& value);
    // returning the memory size
    size_t getSize() const { return memory.size();}
    // printing the memory vector
    void printMemory();
};

#endif // VOLEMACHINE_MEMORY_H
