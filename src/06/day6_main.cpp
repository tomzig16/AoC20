#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../HelperFunctions.h"

struct GroupAnswers {	
	std::map<char, int> groupAnswers;
	int peopleInTheGroup = 0;

	void IncrementAnswer(char letter) {
		if (groupAnswers.find(letter) != groupAnswers.end()) {
			groupAnswers[letter]++;
		}
		else {
			groupAnswers[letter] = 1;
		}
	}
};

std::vector<GroupAnswers> GenerateAnswersForEachGroup(std::vector<std::string> inputs) {
	std::vector<GroupAnswers> result;
	GroupAnswers currentGroupAnswers;
	for (std::string line : inputs) {
		if (line == "") {
			result.push_back(currentGroupAnswers);
			currentGroupAnswers = GroupAnswers();
			continue;
		}
		for (char sym : line) {
			currentGroupAnswers.IncrementAnswer(sym);
		}
		currentGroupAnswers.peopleInTheGroup++;
	}
	result.push_back(currentGroupAnswers);
	return result;
}

int FirstPart(std::vector<GroupAnswers> groupAnswers) {
	int sumOfAll = 0;
	for (GroupAnswers ga : groupAnswers) {
		sumOfAll += ga.groupAnswers.size();
	}
	return sumOfAll;
}

int SecondPart(std::vector<GroupAnswers> groupAnswers) {
	int sumOfAll = 0;
	for (GroupAnswers ga : groupAnswers) {
		for (auto it = ga.groupAnswers.begin(); it != ga.groupAnswers.end(); it++) {
			if (it->second == ga.peopleInTheGroup) sumOfAll++;
		}
	}
	return sumOfAll;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	std::vector<GroupAnswers> groupAnswers = GenerateAnswersForEachGroup(inputs);
	PRINT(1, FirstPart(groupAnswers));
	PRINT(2, SecondPart(groupAnswers));
	return 0;
}