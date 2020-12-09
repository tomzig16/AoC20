#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include "../HelperFunctions.h"

long long FirstPart(std::vector<long long> inputs) {
    for(int i = 25; i < inputs.size(); i++){
        bool hasPair = false;
        for(int j = i - 25; j < i; j++){
            if(hasPair) break;
            for(int k = i - 24; k < i; k++){
                if(j == k) continue;
                if(inputs[j] + inputs[k] == inputs[i]){
                    hasPair = true;
                    break;
                }
            }
        }
        if(!hasPair){
            return inputs[i];
        }
    }
    return -1;
}

long long SecondPart(std::vector<long long> inputs, long long sumOfNumbers) {
    //std::sort(inputs.begin(), inputs.end());
    int startIndex = 0;
    int endIndex = 1;
    long long sumOfSet = inputs[startIndex];
    while(startIndex < inputs.size()){
        sumOfSet += inputs[endIndex];
        if(sumOfSet > sumOfNumbers) {
            startIndex++;
            endIndex = startIndex+1;
            sumOfSet = inputs[startIndex];
            continue;
        }
        if(sumOfSet == sumOfNumbers){
            auto min = std::min_element(inputs.begin() + startIndex, inputs.begin() + endIndex);
            auto max = std::max_element(inputs.begin() + startIndex, inputs.begin() + endIndex);
            return (*min) + (*max);
        }
        if(endIndex+1 == inputs.size()){
            startIndex++;
            endIndex = startIndex+1;
            sumOfSet = inputs[startIndex];
        }
        else{
            endIndex++;
        }
    }
    
    
    return -1;
}

int main() {
    std::vector<long long> inputs = ReadLLongs("input.txt");
    long long part1Res = FirstPart(inputs);
    PRINT(1, part1Res);
    PRINT(2, SecondPart(inputs, part1Res));
    return 0;
}