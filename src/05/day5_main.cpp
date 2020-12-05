#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include <map>
#include "../HelperFunctions.h"

int FirstPart(std::vector<std::string> inputs) {
    int maxID = -1;
	for(std::string line : inputs){
		int maxRow = 127;
		int maxColumn = 7;
		int nOfSeatsInSet = 128;
		for(int i = 0; i < 7; i++){
            nOfSeatsInSet /= 2;
			if(line[i] == 'F'){
				maxRow -= nOfSeatsInSet;
			}
		}
        nOfSeatsInSet = 8;
        for(int i = 7; i < line.size(); i++){
            nOfSeatsInSet /= 2;
			if(line[i] == 'L'){
				maxColumn -= nOfSeatsInSet;
			}
        }
        int currentID = (maxRow * 8) + maxColumn;
        maxID = currentID > maxID ? currentID : maxID;
	}
    return maxID;
}

struct SeatData {
    int row = -1;
    int col = -1;
    int ID = -1;
};

bool CompareSeats(SeatData& lh, SeatData& rh) { return lh.ID < rh.ID; }

int SecondPart(std::vector<std::string> inputs) {
    std::vector<SeatData> sdv;
	for(std::string line : inputs){
		int maxRow = 127;
		int maxColumn = 7;
		int nOfSeatsInSet = 128;
		for(int i = 0; i < 7; i++){
            nOfSeatsInSet /= 2;
			if(line[i] == 'F'){
				maxRow -= nOfSeatsInSet;
			}
		}
        nOfSeatsInSet = 8;
        for(int i = 7; i < line.size(); i++){
            nOfSeatsInSet /= 2;
			if(line[i] == 'L'){
				maxColumn -= nOfSeatsInSet;
			}
        }
        SeatData sd;
        sd.ID = (maxRow * 8) + maxColumn;
        sd.row = maxRow;
        sd.col = maxColumn;
        sdv.push_back(sd);
	}
    std::sort(sdv.begin(), sdv.end(), CompareSeats);
    int missedID = -1;
    for(int i = 1; i < sdv.size(); i++){
        if(sdv[i].ID - sdv[i-1].ID != 1){
            // Assuming that missing seat by one
            missedID = sdv[i-1].ID + 1;
        }
    }
    return missedID;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	PRINT(1, FirstPart(inputs));
	PRINT(2, SecondPart(inputs));
	return 0;
}