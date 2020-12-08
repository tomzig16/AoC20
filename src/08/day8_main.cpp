#include <iostream>
#include <vector>
#include <algorithm>
#include "../HelperFunctions.h"

struct Command {
	std::string op;
	int arg;
	bool wasExecuted = false;
	bool wasChanged = false;

	void RevertJmpVSNop() {
		if (op == "nop") {
			op = "jmp";
			wasChanged = true;
		}
		else if (op == "jmp") {
			op = "nop";
			wasChanged = true;
		}

	}
};

std::vector<Command> allCommands;

void RegisterCommands(std::vector<std::string> inputs) {
	for (std::string input : inputs) {
		Command cmd;
		cmd.op = input.substr(0, input.find(" "));
		input.erase(0, input.find(" ") + 1);
		cmd.arg = StringToInt(input);
		allCommands.push_back(cmd);
	}
}

int FirstPart() {
	int accumulator = 0;
	int cmdIndex = 0;
	while (true) {
		if (allCommands[cmdIndex].wasExecuted) { break; }
		allCommands[cmdIndex].wasExecuted = true;
		if (allCommands[cmdIndex].op == "acc") {
			accumulator += allCommands[cmdIndex].arg;
			cmdIndex++;
		}
		else if (allCommands[cmdIndex].op == "jmp") {
			cmdIndex += allCommands[cmdIndex].arg;
		}
		else if (allCommands[cmdIndex].op == "nop") {
			cmdIndex++;
		}
	}
	return accumulator;
}

int SecondPart() {
	int accumulator = 0;
	int cmdIndex = 0;
	int lastChangedIndex = -1;
	std::vector<int> executedIndices;
	while (cmdIndex < allCommands.size()) {
		if (std::count(executedIndices.begin(), executedIndices.end(), cmdIndex) > 0) { 
			while (executedIndices[executedIndices.size() - 1] != lastChangedIndex) {
				int lastAffectedIndex = executedIndices[executedIndices.size() - 1];
				// revert actions done by executing faulty commands
				if (allCommands[lastAffectedIndex].op == "acc") {
					accumulator -= allCommands[lastAffectedIndex].arg;
				}
				executedIndices.pop_back();
			}
			allCommands[lastChangedIndex].RevertJmpVSNop(); // reverts back
			cmdIndex = lastChangedIndex;
			lastChangedIndex = -1;
			
		}

		// First change the operation
		if (!allCommands[cmdIndex].wasChanged && lastChangedIndex == -1) { // Make sure that we dont change it twice if it fails
			if (allCommands[cmdIndex].op == "jmp" ||
				allCommands[cmdIndex].op == "nop") {
				allCommands[cmdIndex].RevertJmpVSNop();
				lastChangedIndex = cmdIndex;
			}
		}
		// Execute new operation
		executedIndices.push_back(cmdIndex);
		if (allCommands[cmdIndex].op == "acc") {
			accumulator += allCommands[cmdIndex].arg;
			cmdIndex++;
		}
		else if (allCommands[cmdIndex].op == "jmp") {
			cmdIndex += allCommands[cmdIndex].arg;
		}
		else if (allCommands[cmdIndex].op == "nop") {
			cmdIndex++;
		}
	}
	return accumulator;
}

int main() {
	std::vector<std::string> inputs = ReadStrings("input.txt");
	RegisterCommands(inputs);
	PRINT(1, FirstPart());
	PRINT(2, SecondPart());
	return 0;
}
