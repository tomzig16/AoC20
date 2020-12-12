#include <iostream>
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../HelperFunctions.h"

enum FacingDirections {
    NORTH = 1,
    EAST = 2,
    SOUTH = 4,
    WEST = 8
};

struct ShipData {
    int waypointX = 10;
    int waypointY = 1;
    int y = 0;
    int x = 0;
    char facingDir = FacingDirections::EAST;

    // Part 1 related functions
    void DoShipAction(char action, int units) {
        // Expected to get action F, L or R.
        if (action == 'F') {
            if (facingDir == FacingDirections::EAST) x += units;
            if (facingDir == FacingDirections::SOUTH) y -= units;
            if (facingDir == FacingDirections::WEST) x -= units;
            if (facingDir == FacingDirections::NORTH) y += units;
        }
        else {
            Spin(action, units);
        }
    }

    void Spin(char direction, int degrees) {
        // How many times to spin
        for (int i = 0; i < degrees / 90; i++) {
            if (direction == 'R') {
                facingDir = facingDir << 1;
                if (facingDir > 8) {
                    facingDir = FacingDirections::NORTH;
                }
            }
            if (direction == 'L') {
                facingDir = facingDir >> 1;
                if (facingDir == 0) {
                    facingDir = FacingDirections::WEST;
                }
            }
        }
    }
    

    // Part 2 related functions
    void DoShipActionWithWaypoint(char action, int units) {
        // Expected to get action F, L or R.
        if (action == 'F') {
            x = x + (waypointX * units);
            y = y + (waypointY * units);
        }
        else {
            // Can't rely on old direction because in case if waypoint moves to another quarter
            // direction will still remain the same - incorrect one.

            //radians = (degrees * pi) / 180;

            int xQuarter = std::cos((units * M_PI) / 180);
            int yQuarter = std::sin((units * M_PI) / 180);

            int lastQuarter = 0;
            if (waypointX > 0 && waypointY > 0) lastQuarter = 0;
            if (waypointX < 0 && waypointY > 0) lastQuarter = 1;
            if (waypointX < 0 && waypointY < 0) lastQuarter = 2;
            if (waypointX > 0 && waypointY < 0) lastQuarter = 3;
            int newQuarter = action == 'L' ? lastQuarter + (units / 90) : lastQuarter - (units / 90);
            if (newQuarter > 3) newQuarter = newQuarter % 4;
            // Actual spin

            if (waypointX > 0 && waypointY > 0) lastQuarter = 0;
            if (waypointX < 0 && waypointY > 0) lastQuarter = 1;
            if (waypointX < 0 && waypointY < 0) lastQuarter = 2;
            if (waypointX > 0 && waypointY < 0) lastQuarter = 3;
        }
    }
};


std::vector<std::pair<char, int>> GenerateInstructionArray(std::vector<std::string> inputs) {
    std::vector<std::pair<char, int>> outp;
    for (std::string line : inputs) {
        std::pair<char, int> inp;
        inp.first = line[0];
        line.erase(0, 1);
        inp.second = StringToInt(line);
        outp.push_back(inp);
    }
    return outp;
}

int FirstPart(std::vector<std::pair<char, int>> instrArray) {
    ShipData shipData;
    for (std::pair<char, int> singleInstruction : instrArray) {
        if (singleInstruction.first == 'N') {
            shipData.y += singleInstruction.second;
        }
        else if (singleInstruction.first == 'E') {
            shipData.x += singleInstruction.second;
        }
        else if (singleInstruction.first == 'S') {
            shipData.y -= singleInstruction.second;
        }
        else if (singleInstruction.first == 'W') {
            shipData.x -= singleInstruction.second;
        }
        else {
            shipData.DoShipAction(singleInstruction.first, singleInstruction.second);
        }
    }
    return std::abs(shipData.x) + std::abs(shipData.y);
}

int SecondPart(std::vector<std::pair<char, int>> instrArray) {
    // @TODO
    return 1;
    ShipData shipData;
    for (std::pair<char, int> singleInstruction : instrArray) {
        if (singleInstruction.first == 'N') {
            shipData.waypointY += singleInstruction.second;
        }
        else if (singleInstruction.first == 'E') {
            shipData.waypointX += singleInstruction.second;
        }
        else if (singleInstruction.first == 'S') {
            shipData.waypointY -= singleInstruction.second;
        }
        else if (singleInstruction.first == 'W') {
            shipData.waypointX -= singleInstruction.second;
        }
        else {
            shipData.DoShipAction(singleInstruction.first, singleInstruction.second);
        }
    }
    return std::abs(shipData.x) + std::abs(shipData.y);
}

int main() {
    std::vector<std::string> inputs = ReadStrings("input.txt");
    std::vector<std::pair<char, int>> instrArr = GenerateInstructionArray(inputs);
    PRINT(1, FirstPart(instrArr));
    PRINT(2, SecondPart(instrArr));
    return 0;
}