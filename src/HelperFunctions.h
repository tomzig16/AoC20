#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#define PRINT(taskn, res) do{ std::cout << "(" << taskn << ") Result: " << res << "\n";}while(0)

int StringToInt(std::string str) {
	std::stringstream sstr(str);
	int num = 0;
	sstr >> num;
	return num;
}

std::vector<int> ReadIntegers(std::string filePath) {
	std::vector<int> output;
	std::ifstream f(filePath);
	if (f.is_open()) {
		std::string line;
		while (std::getline(f, line)) {
			output.push_back(StringToInt(line));
		}
	}
	f.close();
	return output;
}

std::vector<std::string> ReadStrings(std::string filePath) {
	std::vector<std::string> output;
	std::ifstream f(filePath);
	if (f.is_open()) {
		std::string line;
		while (std::getline(f, line)) {
			output.push_back(line);
		}
	}
	f.close();
	return output;
}


#endif // HELPER_H