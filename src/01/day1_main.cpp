#include <iostream>
#include <vector>
#include "../HelperFunctions.h"

int FirstPart(std::vector<int> inputs) {
	for (int i = 0; i < inputs.size(); i++) {
		for (int j = 1; j < inputs.size(); j++) {
			if (i == j) continue;
			if (inputs[i] + inputs[j] == 2020) {
				return inputs[i] * inputs[j];
			}
		}
	}
}

int SecondPart(std::vector<int> inputs) {
	for (int i = 0; i < inputs.size(); i++) {
		for (int j = 1; j < inputs.size(); j++) {
			for (int k = 2; k < inputs.size(); k++) {
				if (i == j || j == k || i == k) continue;
				if (inputs[i] + inputs[j] + inputs[k] == 2020) {
					return inputs[i] * inputs[j] * inputs[k];
				}
			}
		}
	}
}

int main() {
	std::vector<int> inputs = ReadIntegers("input.txt");
	std::cout << "(1) result: " << FirstPart(inputs) << "\n";
	std::cout << "(2) result: " << SecondPart(inputs) << "\n";
	return 0;
}