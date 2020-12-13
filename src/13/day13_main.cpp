#include <iostream>
#include <vector>
#include <algorithm>
#include "../HelperFunctions.h"

typedef unsigned long long t_ULL;

int FirstPart(int minTime, std::vector<int> knownBusses) {
    std::vector<std::pair<int, int>> earliestAvailable;
    for (int busID : knownBusses) {
        int remainder = minTime % busID;
        earliestAvailable.push_back(std::pair<int, int>(busID, (busID - remainder) + minTime));
    }
    std::sort(earliestAvailable.begin(), earliestAvailable.end(),
        [](std::pair<int, int> ls, std::pair<int, int> rs) {
        return ls.second < rs.second;
    });
    return earliestAvailable[0].first * (earliestAvailable[0].second - minTime);
}

// 640856202464541 is correct answer.
// Very ineficcient way of finding
t_ULL SecondPart(std::string inputWithAllBusses) {
    // First number is offset from first bus
    // Second number is actual bus ID
    std::vector<std::pair<int, int>> allBusses;
    int busSequenceNumber = 0;
    while (inputWithAllBusses.size() > 0) {
        size_t nextComma = inputWithAllBusses.find(",");
        if (nextComma == inputWithAllBusses.npos) nextComma = inputWithAllBusses.size();
        std::string busID = inputWithAllBusses.substr(0, nextComma);
        inputWithAllBusses.erase(0, nextComma + 1);

        if (busID == "x") {
            busSequenceNumber++;
            continue;
        }
        allBusses.push_back(std::pair<int, int>(busSequenceNumber++, StringToInt(busID)));
    }

    
    // first number is index of first paired entry from allBusses
    // second number is index of second paired entry from allBusses
    std::vector<std::pair<int, int>> pairs; // numbers that contain pairs (second number contains pair with another number)
    for (int i = 0; i < allBusses.size(); i++) {
        for (int j = i+1; j < allBusses.size(); j++) {
            if (allBusses[i].second == allBusses[j].first) {
                pairs.push_back(std::pair<int, int>(i, j));
            }
            // If performance of the loop is bad, add check if modulus of two numbers is 0
            // those could be used as pairs too
        }
    }

    auto largestNumberIT = std::max_element(allBusses.begin(), allBusses.end(),
        [](std::pair<int, int> ls, std::pair<int, int> rs) {
        return ls.second < rs.second;
    });
    t_ULL largestNumberOffset = 41;
    t_ULL largestNumber = 911;
    // Buggest jumps would add biggest numbers in busses array, 
    // however real result is hiding in 't' value, which is offset
    // of the very first entry
    t_ULL realResult;
    t_ULL start = 640856202400000 + (largestNumber - (640856202400000 % largestNumber));
    for (t_ULL currentT = start; 1; currentT += largestNumber) {
        if ((currentT - largestNumberOffset) % (t_ULL)allBusses[0].second != 0) {
            continue;
        }
        else {
            realResult = currentT - largestNumberOffset;
        }
        bool skipFurtherChecks = false;
        for (auto pair : pairs) {
            if (((realResult + (t_ULL)allBusses[pair.first].first) % // add offset
                (t_ULL)allBusses[pair.first].second != 0) ||
                ((realResult + (t_ULL)allBusses[pair.second].first) % // add offset
                (t_ULL)allBusses[pair.second].second != 0)) {
                skipFurtherChecks = true;
                break;
            }
        }
        if (skipFurtherChecks) { continue; }
        // we already checked id 0 as the first thing
        for (int i = 1; i < allBusses.size(); i++) {
            if ((realResult + (t_ULL)allBusses[i].first) % (t_ULL)allBusses[i].second != 0) {
                skipFurtherChecks = true;
                break;
            }
        }
        if (skipFurtherChecks) { 
            continue; 
        }
        else { 
            break; 
        } // result was found
    }

    return realResult;
}

std::vector<int> RemoveUnknownBusses(std::string allBusses) {
    std::vector<int> inputs;
    while (allBusses.size() > 0) {
        size_t nextComma = allBusses.find(",");
        if (nextComma == allBusses.npos) nextComma = allBusses.size();
        std::string busID = allBusses.substr(0, nextComma);
        allBusses.erase(0, nextComma + 1);

        if (busID == "x") {
            continue;
        }
        inputs.push_back(StringToInt(busID));
    }
    return inputs;
}

int main() {
    std::vector<std::string> inputs = ReadStrings("input.txt");
    int earliestTime = StringToInt(inputs[0]);
    std::vector<int> knownBusses = RemoveUnknownBusses(inputs[1]);
    PRINT(1, FirstPart(earliestTime, knownBusses));
    PRINT(2, SecondPart(inputs[1]));
    return 0;
}