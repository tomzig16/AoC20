#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include "../HelperFunctions.h"

struct ShipMemory {
    int64_t bits; // 64 bits total (8 bytes)
                  // mask holds 36 bits
    int GetBit(int index) {
        int64_t powOfTwo = std::pow(2, index);
        return bits & powOfTwo;
    }

    void OverwriteValue(int64_t value, std::string bitmask) {
        int64_t finalValue = 0;
        // increment bit index and decrement letter index, as string is read from left to right
        // while bitmask is noted from right to left
        for (int letterI = 35, bitI = 0; letterI >= 0; letterI--, bitI++) {
            if (bitmask[letterI] == 'X') {
                if((value & (int64_t)std::pow(2, bitI)) > 0) 
                    finalValue = finalValue | (int64_t)std::pow(2, bitI);
            }
            else if (bitmask[letterI] == '1') finalValue = finalValue | (int64_t)std::pow(2, bitI);
            else if (bitmask[letterI] == '0') finalValue = finalValue & ~(int64_t)std::pow(2, bitI);
        }
        bits = finalValue;
    }
};

int64_t FirstPart(std::vector<std::string> inputs) {
    std::map<std::string, ShipMemory> wholeShipMemory;
    std::string currentMask;
    for (std::string line : inputs) {
        if (line.find("mask") != line.npos) {
            currentMask = line.substr(line.find('=') + 2, 36); // read 36 bits
        }
        else { // mem[i]
            std::regex memRegex("mem\\[(\\d+)\\] = (\\d+)");
            std::sregex_iterator regRes = std::sregex_iterator(line.begin(), line.end(), memRegex);
            std::smatch match = *regRes;
            wholeShipMemory[match[1]].OverwriteValue(StringToLLong(match[2]), currentMask);
        }
    }
    int64_t sum = 0;
    for (auto i = wholeShipMemory.begin(); i != wholeShipMemory.end(); i++) {
        sum += i->second.bits;
    }
    return sum;
}

int SecondPart(std::string inputWithAllBusses) {
    return -1;
}


int main() {
    std::vector<std::string> inputs = ReadStrings("input.txt");
    PRINT(1, FirstPart(inputs));
    PRINT(2, SecondPart(inputs[1]));
    return 0;
}