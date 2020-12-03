#include <iostream>
#include <vector>
#include <algorithm>
#include "../HelperFunctions.h"

int FirstPart(std::vector<std::string> inputs) {
	int totalCount = 0;
	int lineLength = inputs[0].size();
	int posX = 3;
	for (int i = 1; i < inputs.size(); i++) {
		if (inputs[i][posX] == '#') {
			totalCount++;
		}
		posX += 3;
		if (posX >= lineLength) {
			posX -= lineLength;
		}
	}
	return totalCount;
}

long long SecondPart(std::vector<std::string> inputs, int moveRight, int moveDown) {
	if (moveRight == -1) {
		long long result = 1;
		result *= SecondPart(inputs, 1, 1);
		result *= SecondPart(inputs, 3, 1);
		result *= SecondPart(inputs, 5, 1);
		result *= SecondPart(inputs, 7, 1);
		result *= SecondPart(inputs, 1, 2);
		return result;
	}
	int totalCount = 0;
	int lineLength = inputs[0].size();
	int posX = moveRight;
	for (int i = moveDown; i < inputs.size(); i+=moveDown) {
		if (inputs[i][posX] == '#') {
			totalCount++;
		}
		posX += moveRight;
		if (posX >= lineLength) {
			posX -= lineLength;
		}
	}
	return totalCount;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	PRINT(1, FirstPart(inputs));
	PRINT(2, SecondPart(inputs, -1, -1));
	return 0;
}
