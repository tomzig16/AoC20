#include <iostream>
#include <vector>
#include <algorithm>
#include "../HelperFunctions.h"

int FirstPart(std::vector<int> inputs) {
    inputs.push_back(0); // we start with 0
    std::sort(inputs.begin(), inputs.end());
    int diffByOne = 0;
    int diffByThree = 1; // added one as biggest diff is always +3 by default
    for (int i = 1; i < inputs.size(); i++) {
        switch (inputs[i] - inputs[i - 1]) {
        case 1:
            diffByOne++;
            break;
        case 3:
            diffByThree++;
            break;
        default:
            std::cout << "Diff by two or more/less has been found!\n";
            break;
        }
    }
    return diffByOne * diffByThree;
}


// Very bad implementation, took 3 hours to find an answer.
// Needs at least caching
std::vector<int> inputsForPart2;
long long RecursivePart2(int index) {
    long long result = 0;
    if (index == inputsForPart2.size() - 2) {
        if (inputsForPart2[index + 1] - inputsForPart2[index] == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }

    if (inputsForPart2[index + 1] - inputsForPart2[index] <= 3) {
        result += RecursivePart2(index + 1);
    }
    if (inputsForPart2[index + 2] - inputsForPart2[index] <= 3) {
        result += RecursivePart2(index + 2);
    }
    if ((index < inputsForPart2.size() - 3) && (inputsForPart2[index + 3] - inputsForPart2[index] <= 3)) {
        result += RecursivePart2(index + 3);
    }
    return result;
}

long long SecondPart(std::vector<int> inputs) {
    inputs.push_back(0); // we start with 0
    std::sort(inputs.begin(), inputs.end());
    inputs.push_back(inputs[inputs.size() - 1] + 3);
    inputsForPart2 = inputs;
    return RecursivePart2(0);
    
}

int main() {
    std::vector<int> inputs = ReadIntegers("input.txt");
    PRINT(1, FirstPart(inputs));
    PRINT(2, SecondPart(inputs));
    return 0;
}
