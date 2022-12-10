#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <stack>
#include <vector>

std::vector<std::string> ReadLines(std::string fileName){
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> Split(std::string string, char * delimiter) {
    std::vector<std::string> tokens{};
    char * token = std::strtok((char*)string.c_str(), delimiter);
    while (token != nullptr) {
        tokens.push_back(std::string(token));
        token = strtok(nullptr, delimiter);
    }
    return tokens;
}

void MoveItems(std::stack<char> &fromStack, std::stack<char> &toStack, int num) {
    for (int i = 0; i < num; i++){
        char item = fromStack.top();
        fromStack.pop();
        toStack.push(item);
    }
}

void MoveItemsStacked(std::stack<char> &fromStack, std::stack<char> &toStack, int num) {
    char item;
    std::stack<char> tempStack;
    for (int i = 0; i < num; i++){
        item = fromStack.top();
        fromStack.pop();
        tempStack.push(item);
    }
    for (int i = 0; i < num; i++){
        item = tempStack.top();
        tempStack.pop();
        toStack.push(item);
    }
}

int main() {
    std::vector<std::string> lines(ReadLines("stacks.txt"));

    int blankIndex;
    for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
        if (!lines[lineIndex].size()) {
            blankIndex = lineIndex;
        }
    }

    std::vector<std::stack<char>> stacks{};
    for (int columnIndex = 0; columnIndex < lines[blankIndex-1].size(); columnIndex++) {
        if (lines[blankIndex-1][columnIndex] != ' ') {
            std::stack<char> _stack{};
            for (int lineIndex = blankIndex-2; lineIndex >= 0 ; lineIndex--){
                if (lines[lineIndex][columnIndex] == ' ') {
                    break;
                }
                _stack.push(lines[lineIndex][columnIndex]);
            }
            stacks.push_back(_stack);
        }
    }
    std::vector<std::stack<char>> stacks2{stacks};

    for (int lineIndex = blankIndex + 1; lineIndex < lines.size(); lineIndex++) {
        char delimiter = ' ';
        std::vector<std::string> tokens = Split(lines[lineIndex], &delimiter);
        MoveItems(stacks[std::stoi(tokens[3]) - 1], stacks[std::stoi(tokens[5]) - 1], std::stoi(tokens[1]));
        MoveItemsStacked(stacks2[std::stoi(tokens[3]) - 1], stacks2[std::stoi(tokens[5]) - 1], std::stoi(tokens[1]));
    }

    std::string topItems{""};
    for (std::stack<char> s: stacks){
        topItems += s.top();
    }
    std::cout << "Items on top: " << topItems << std::endl;

    std::string topItems2{""};
    for (std::stack<char> s: stacks2){
        topItems2 += s.top();
    }
    std::cout << "Items on top 2: " << topItems2 << std::endl;
    
    return 0;
}
