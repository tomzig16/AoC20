#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include "../HelperFunctions.h"

struct PassportData {
	std::map<std::string, std::string> data;
	void AddData(std::string key, std::string val) {
		data[key] = val;
	}

	bool IsValidPassport() {
		return (data.size() == 8) ||
			((data.size() == 7) && (data.find("cid") == data.end()));
	}
};


std::vector<PassportData> GeneratePassportData(std::vector<std::string> inputs) {
	std::vector<PassportData> outputData;
	PassportData currentPerson;
	for (std::string line : inputs) {
		if (line == "") { // Person passport data has ended
			outputData.push_back(currentPerson);
			currentPerson = PassportData();
			continue;
		}
		size_t posOfColon = -1;
		while ((posOfColon = line.find(":")) != line.npos) {
			std::string key = line.substr(0, posOfColon);
			std::string value;
			size_t posOfEndVal = line.find(" "); // first lets find space
			size_t howMuchToSubstr;
			if (posOfEndVal == line.npos) {
				howMuchToSubstr = line.size();
			}
			else {
				// posOfEndVal in this case becomes how many chars to read
				howMuchToSubstr = posOfEndVal - posOfColon - 1;
			}
			value = line.substr(posOfColon + 1, howMuchToSubstr);
			currentPerson.AddData(key, value);
			if (howMuchToSubstr != line.size()) {
				line.erase(0, posOfEndVal + 1);
			}
			else {
				// Instead of deleting string we can just break. 
				// Saves performance.
				break;
			}
		}
	}
	if (currentPerson.data.size() > 0) {
		// Save last person as there's no guarantee that 
		// file will have extra empty lines at the end
		outputData.push_back(currentPerson);
	}
	return outputData;
}

int FirstPart(std::vector<PassportData> passportData) {
	int counter = 0;
	for (PassportData pd : passportData) {
		if (pd.IsValidPassport()) counter++;
	}
	return counter;
}

int SecondPart(std::vector<std::string> inputs) {
	return -1;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	std::vector<PassportData> pd = GeneratePassportData(inputs);
	PRINT(1, FirstPart(pd));
	PRINT(2, SecondPart(inputs));
	return 0;
}