#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "monkey.h"

// set numRounds = 20 and leastCommonMultiple = 0 for part 1
int numRounds{10000};
int leastCommonMultiple{1};

std::vector<std::string> ReadLines(std::string fileName){
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> Split(std::string string, const char* delimiter) {
    std::vector<std::string> tokens{};
    char * token = std::strtok((char*)string.c_str(), delimiter);
    while (token != nullptr) {
        tokens.push_back(std::string(token));
        token = strtok(nullptr, delimiter);
    }
    return tokens;
}

int main() {
    std::vector<std::string> monkeys{ReadLines("monkeys.txt")};
    std::vector<Monkey> M{};
    for (int i = 0;  i < monkeys.size() ; i += 7) {
        std::vector<std::string> monkey{monkeys.begin() + i, monkeys.begin() + i + 6};

        std::vector<int> startingItems{};
        for (std::string item : Split(Split(monkey[1], ":")[1], ",")) {
            startingItems.push_back(std::stoi(item));
        }
        std::vector<std::string> operation{Split(Split(monkey[2], "=")[1], " ")};
        int testDenominator{std::stoi(Split(monkey[3], " ").back())};
        leastCommonMultiple *= testDenominator;
        int testTrue{std::stoi(Split(monkey[4], " ").back())};
        int testFalse{std::stoi(Split(monkey[5], " ").back())};

        M.push_back({startingItems, operation, testDenominator, testTrue, testFalse});
    }

    for (int round = 0; round < numRounds; round++) {
        for (int i = 0; i < M.size(); i++) {
            for (std::array<long,2> t : M[i].Throw(leastCommonMultiple)){
                M[t[1]].Catch(t[0]);
            }
        }
    }

    int numInspects[M.size()];
    for (int i = 0; i < M.size(); i++) {
        numInspects[i] = M[i].NumInspects();
    }
    int n = sizeof(numInspects) / sizeof(numInspects[0]);
    std::sort(numInspects, numInspects + n, std::greater<int>());
    std::cout << "MonkeyBusiness: " << long(numInspects[0]) * long(numInspects[1]) << std::endl;

    return 0;
}

