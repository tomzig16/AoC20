#include <iostream>
#include <vector>
#include <regex>
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

	// byr, iyr and eyr have the same requirements but different min max
	bool YearIsValid(std::string key, int min, int max) {
		std::string val = data[key];
		if (val.size() != 4) return false;
		int number = StringToInt(val);
		return number >= min && number <= max;
	}

	bool HgtIsValid() {
		std::string val = data["hgt"];
		std::string units = val.substr(val.size() - 2, 2);
		val.erase(val.size() - 2, val.size());
		int number = StringToInt(val);
		if (units == "cm") {
			return number >= 150 && number <= 193;
		}
		else if (units == "in") {
			return number >= 59 && number <= 76;
		}
		return false;
	}

	bool HclIsValid() {
		std::string val = data["hcl"];
		std::regex regexForColor("^#[a-fA-F0-9]{6}$");
		return std::regex_search(val, regexForColor);
	}

	bool EclIsValid() {
		std::string val = data["ecl"];
		return
			val == "amb" ||
			val == "blu" ||
			val == "brn" ||
			val == "gry" ||
			val == "grn" ||
			val == "hzl" ||
			val == "oth";
	}

	bool PidIsValid() {
		std::string val = data["pid"];
		std::regex regexForColor("^\\d{9}$");
		return std::regex_search(val, regexForColor);
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

int SecondPart(std::vector<PassportData> passportData) {
	int counter = 0;
	for (PassportData pd : passportData) {
		if (!pd.IsValidPassport()) continue;
		if(!pd.YearIsValid("byr", 1920, 2002)) continue;
		if(!pd.YearIsValid("iyr", 2010, 2020)) continue;
		if(!pd.YearIsValid("eyr", 2020, 2030)) continue;
		if(!pd.HgtIsValid()) continue;
		if(!pd.HclIsValid()) continue;
		if(!pd.EclIsValid()) continue;
		if(!pd.PidIsValid()) continue;
		counter++;
	}
	return counter;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	std::vector<PassportData> pd = GeneratePassportData(inputs);
	PRINT(1, FirstPart(pd));
	PRINT(2, SecondPart(pd));
	return 0;
}