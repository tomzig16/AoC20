#include <iostream>
#include <vector>
#include <algorithm>
#include "../HelperFunctions.h"

int FirstPart(std::vector<std::string> inputs) {
	int totalCount = 0;
	for (std::string input : inputs) {
		int min, max;
		std::string letter;
		std::string password;

		min = StringToInt(input.substr(0, input.find('-')));
		input.erase(0, input.find('-') + 1);

		max = StringToInt(input.substr(0, input.find(' ')));
		input.erase(0, input.find(' ') + 1);

		letter = input.substr(0, input.find(": "));
		input.erase(0, input.find(": ") + 2);

		password = input;

		size_t count = std::count_if(
			password.begin(),
			password.end(),
			[&](char symbolFromPassw) { 
				if (symbolFromPassw == letter[0])
					return true;
				else
					return false;
			});
		if (count >= min && count <= max) totalCount++;
	}
	return totalCount;
}

int SecondPart(std::vector<std::string> inputs) {
	int totalCount = 0;
	for (std::string input : inputs) {
		int firstOption, secondOption;
		std::string letter;
		std::string password;

		firstOption = StringToInt(input.substr(0, input.find('-'))) - 1;
		input.erase(0, input.find('-') + 1);

		secondOption = StringToInt(input.substr(0, input.find(' '))) - 1;
		input.erase(0, input.find(' ') + 1);

		letter = input.substr(0, input.find(": "));
		input.erase(0, input.find(": ") + 2);

		password = input;
		if (!(password[firstOption] == letter[0]) != !(password[secondOption] == letter[0])) {
			totalCount++;
		}
	}
	return totalCount;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	PRINT(1, FirstPart(inputs));
	PRINT(2, SecondPart(inputs));
	return 0;
}