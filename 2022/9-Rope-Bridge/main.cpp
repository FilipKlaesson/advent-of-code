#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>

typedef  std::array<int, 2> pos;

std::map<char, int> rowDirection{{'L',0}, {'U',-1}, {'R',0}, {'D',1}};
std::map<char, int> columnDirection{{'L',-1}, {'U',0}, {'R',1}, {'D',0}};

std::tuple<char, int> Split(std::string string) {
    const char* delimiter{" "};
    std::vector<std::string> tokens{};
    char * token = std::strtok((char*)string.c_str(), delimiter);
    char move{*token};
    token = strtok(nullptr, delimiter);
    int amount{std::stoi(std::string(token))};
    return std::tuple<char, int>{move, amount};
}

std::vector<std::tuple<char,int>> ReadLines(std::string fileName){
    std::ifstream file(fileName);
    std::vector<std::tuple<char,int>> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(Split(line));
    }
    return lines;
}

void MoveTail(pos &head, pos &tail) {
    int rowDistance{abs(head[0] - tail[0])};
    int columnDistance{abs(head[1] - tail[1])};
    if (rowDistance == 2 && columnDistance == 2) {
        if (head[0] > tail[0]) {
            tail[0] = head[0] - 1;
        } else {
            tail[0] = head[0] + 1;
        }
        if (head[1] > tail[1]) {
            tail[1] = head[1] - 1;
        } else {
            tail[1] = head[1] + 1;
        }
    }
    else if (rowDistance == 2) {
        if (head[0] > tail[0]) {
            tail[0] = head[0] - 1;
        } else {
            tail[0] = head[0] + 1;
        }
        tail[1] = head[1];
    }
    else if (columnDistance >= 2) {
        tail[0] = head[0];
        if (head[1] > tail[1]) {
            tail[1] = head[1] - 1;
        } else {
            tail[1] = head[1] + 1;
        }
    }
    return;
}

int main() {
    pos head{0,0};
    std::array<pos,9> tails;
    for (int i = 0; i < 9; i++) {
        tails[i] = {0,0};
    }
    std::set<pos> tailPositionsFirst{tails[0]};
    std::set<pos> tailPositionsLast{tails[8]};
    std::vector<std::tuple<char, int>> moves{ReadLines("moves.txt")};
    for (std::tuple<char, int> move : moves) {
        for (int i = 0; i < std::get<1>(move); i++) {
            char direction{std::get<0>(move)};
            head[0] += rowDirection[direction];
            head[1] += columnDirection[direction];
            MoveTail(head, tails[0]);
            for (int j = 1; j < 9; j++) {
                MoveTail(tails[j-1], tails[j]);
            }
            tailPositionsFirst.insert(tails[0]);
            tailPositionsLast.insert(tails[8]);
        }
    }
    std::cout << "Number of different first tail positions: " << tailPositionsFirst.size() << std::endl;
    std::cout << "Number of different last tail positions: " << tailPositionsLast.size() << std::endl;
    return 0;
}
