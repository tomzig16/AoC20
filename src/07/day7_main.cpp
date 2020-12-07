#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include "../HelperFunctions.h"


struct BagData {
	std::string name;
	std::map<BagData*, int> contains;
	std::vector<BagData*> containedIn;
	bool visitedForPart1 = false;

	BagData() {};
	BagData(std::string _name) : name(_name) {};

	void CountPart1(int& result) {
		int localResult = 0;
		visitedForPart1 = true;
		for (int i = 0; i < containedIn.size(); i++) {
			if (!containedIn[i]->visitedForPart1)
			{
				localResult++;
			}
			containedIn[i]->CountPart1(result);
		}
		result += localResult;
	}

	int CountPart2() {
		int localResult = 0;
		for (auto i = contains.begin(); i != contains.end(); i++) {
			int currentBag = i->first->CountPart2();
			localResult += currentBag * i->second;
		}
		if(name != "shiny gold") localResult += 1; // account for this bag
		return localResult;
	}
};

std::map<std::string, BagData> allBagsData; 

void PopulateBagMap(std::vector<std::string> inputs) {
	for (std::string input : inputs) {
		std::string thisBagName = input.substr(0, input.find(" bags contain"));
		input.erase(0, input.find(" bags contain") + std::string(" bags contain ").size());
		if (allBagsData.find(thisBagName) != allBagsData.end()) {
			// Bag is already added but for easier debug reasons add name to the struct itself
			allBagsData[thisBagName].name = thisBagName;
		}
		else {
			allBagsData[thisBagName] = BagData(thisBagName);
		}
		if (input.find("no other bag") != input.npos) continue;

		std::regex bagDataRegex("((\\d) ([a-z]* [a-z]*) bags?)(, |\\.)");
		// 0 - whole thin
		// 1 - number and word
		// 2 - first number
		// 3 - name of the bag
		auto regRes = std::sregex_iterator(input.begin(), input.end(), bagDataRegex);
		auto regResEnd = std::sregex_iterator();
		for (auto i = regRes; i != regResEnd; i++) {
			std::smatch match = *i;
			std::string bagInfoName = match[3];
			std::string bagQuantity = match[2];
			allBagsData[bagInfoName].containedIn.push_back(&allBagsData[thisBagName]);
			allBagsData[thisBagName].contains[&allBagsData[bagInfoName]] = StringToInt(bagQuantity);
		}
	}
}

int FirstPart() {
	int result = 0;
	allBagsData["shiny gold"].CountPart1(result);
	return result;
}

int SecondPart() {
	int totalCount = allBagsData["shiny gold"].CountPart2();
	return totalCount;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	PopulateBagMap(inputs);
	PRINT(1, FirstPart());
	PRINT(2, SecondPart());
	return 0;
}