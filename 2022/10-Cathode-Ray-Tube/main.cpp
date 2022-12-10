#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

std::vector<int> cycles{20, 60, 100, 140, 180, 220};
int crtWidth{40};

std::vector<std::string> ReadLines(std::string fileName){
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int GetAddXValue(std::string string) {
    const char* delimiter{" "};
    std::vector<std::string> tokens{};
    char * token = std::strtok((char*)string.c_str(), delimiter);
    token = strtok(nullptr, delimiter);
    return std::stoi(std::string(token));
}

bool Exist(std::vector<int> v, int e) {
    return std::find(std::begin(v), std::end(v), e) != std::end(v);
}

void SetPixel(std::string &pixels, int cycle, int X) {
    int pixel{(cycle-1)%crtWidth};
    if (pixel >= X - 1 && pixel <= X + 1) {
        pixels += '#';
    } else {
        pixels += ' ';
    }
    return;
}

void Draw(std::string &pixels) {
    for (int i = 0 ; i < pixels.size(); i+=crtWidth) {
        std::cout << pixels.substr(i, crtWidth) << std::endl;
    }
    return;
}

int main() {
    int cycle{0};
    int X{1};
    int signalSum{0};
    std::string pixels;
    std::vector<std::string> instructions{ReadLines("instructions.txt")};
    for (std::string instruction: instructions) {
        cycle++;
        SetPixel(pixels, cycle, X);
        if (instruction == "noop") {
            if (Exist(cycles, cycle)){
                signalSum += X * cycle;
            } 
        } else {
            if (Exist(cycles, cycle)){
                signalSum += X * cycle;
            }
            cycle++;
            SetPixel(pixels, cycle, X);
            if (Exist(cycles, cycle)){
                signalSum += X * cycle;
            }
            X += GetAddXValue(instruction);
        }
    }
    std::cout << "Sum of signal strengths: " << signalSum << std::endl;
    std::cout << "CRT output:" << std::endl;
    Draw(pixels);
    return 0;
}
