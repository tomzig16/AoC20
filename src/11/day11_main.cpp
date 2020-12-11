#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include "../HelperFunctions.h"

struct SeatData {
    bool isFloor = false;
    bool isOccupied = false;
    bool isChangedNextRound = false;

    void UpdateSeatState() {
        if (isChangedNextRound) {
            isOccupied = !isOccupied;
        }
        isChangedNextRound = false;
    }
};

#define CharMatrix std::vector<std::vector<SeatData>>

CharMatrix GenerateSeatMatrix(std::vector<std::string> inputs) {
    CharMatrix outp;
    for (std::string line : inputs) {
        std::vector<SeatData> seatsInLine;
        for (char sym : line) {
            SeatData sd;
            if (sym == '.') sd.isFloor = true;
            else if (sym == '#') sd.isOccupied = true;
            seatsInLine.push_back(sd);
        }
        outp.push_back(seatsInLine);
    }
    return outp;
}

int FirstPart(CharMatrix allSeats) {
    bool hasSomethingChanged = true;
    int nOfRows = allSeats.size();
    int nOfCols = allSeats[0].size();
    int nOfRounds = 0;
    while (hasSomethingChanged) {
        hasSomethingChanged = false;
        for (int i = 0; i < nOfRows; i++) {
            for (int j = 0; j < nOfCols; j++) {
                if (allSeats[i][j].isFloor) continue; // we dont check floor
                // check each seat around
                int nOfTaken = 0;
                for (int row = i - 1; row < i + 2; row++) {
                    if (row >= nOfRows || row < 0) continue; // out of bounds
                    for (int col = j - 1; col < j + 2; col++) {
                        if (col >= nOfCols || col < 0 || (row == i && col == j)) continue; // out of bounds + self check
                        if (allSeats[row][col].isOccupied) nOfTaken++;
                    }
                }
                if (allSeats[i][j].isOccupied && nOfTaken >= 4) {
                    hasSomethingChanged = true;
                    allSeats[i][j].isChangedNextRound = true;
                }
                else if (!allSeats[i][j].isOccupied && nOfTaken == 0) {
                    hasSomethingChanged = true;
                    allSeats[i][j].isChangedNextRound = true;
                }
            }
        }
        if (hasSomethingChanged) {
            for (int i = 0; i < allSeats.size(); i++) {
                for (int j = 0; j < allSeats[0].size(); j++) {
                    allSeats[i][j].UpdateSeatState();
                }
            }
        }
        nOfRounds++;
    }
    int nOfTaken = 0;
    for (auto seatRow : allSeats) {
        for (auto singleSeat : seatRow) {
            if (singleSeat.isFloor) continue;
            if (singleSeat.isOccupied) nOfTaken++;;
        }
    }
    return nOfTaken;
}

int SecondPart(CharMatrix allSeats) {
    bool hasSomethingChanged = true;
    int nOfRows = allSeats.size();
    int nOfCols = allSeats[0].size();
    int nOfRounds = 0;
    while (hasSomethingChanged) {
        hasSomethingChanged = false;
        for (int i = 0; i < nOfRows; i++) {
            for (int j = 0; j < nOfCols; j++) {
                if (allSeats[i][j].isFloor) continue; // we dont check floor
                // check each seat around
                int nOfTaken = 0;
                int lookDirV = -1;
                for (int row = i - 1; row < i + 2; row++) {
                    if (row >= nOfRows || row < 0) {
                        lookDirV++;
                        continue; // out of bounds
                    }
                    int lookDirH = -1;
                    for (int col = j - 1; col < j + 2; col++) {
                        if (col >= nOfCols || col < 0 || (row == i && col == j)) {
                            lookDirH++; 
                            continue; // out of bounds + self check
                        }
                        int lookAtV = row;
                        int lookAtH = col;
                        while (allSeats[lookAtV][lookAtH].isFloor) {
                            // if something goes out of bounds then just break the loop with last available item
                            if ((lookAtH + lookDirH >= nOfCols || lookAtH + lookDirH < 0) ||
                                (lookAtV + lookDirV >= nOfRows || lookAtV + lookDirV < 0)) {
                                break;
                            }
                            lookAtV += lookDirV;
                            lookAtH += lookDirH;
                        }
                        if (allSeats[lookAtV][lookAtH].isOccupied) nOfTaken++;
                        lookDirH++;
                    }
                    lookDirV++;
                }
                if (allSeats[i][j].isOccupied && nOfTaken >= 5) {
                    hasSomethingChanged = true;
                    allSeats[i][j].isChangedNextRound = true;
                }
                else if (!allSeats[i][j].isOccupied && nOfTaken == 0) {
                    hasSomethingChanged = true;
                    allSeats[i][j].isChangedNextRound = true;
                }
            }
        }
        if (hasSomethingChanged) {
            for (int i = 0; i < allSeats.size(); i++) {
                for (int j = 0; j < allSeats[0].size(); j++) {
                    allSeats[i][j].UpdateSeatState();
                }
            }
        }
        nOfRounds++;
    }
    int nOfTaken = 0;
    for (auto seatRow : allSeats) {
        for (auto singleSeat : seatRow) {
            if (singleSeat.isFloor) continue;
            if (singleSeat.isOccupied) nOfTaken++;;
        }
    }
    return nOfTaken;
}

int main() {
    std::vector<std::string> inputs = ReadStrings("input.txt");
    CharMatrix cm = GenerateSeatMatrix(inputs);
    //PRINT(1, FirstPart(cm));
    PRINT(2, SecondPart(cm));
    return 0;
}