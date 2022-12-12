#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include <algorithm>
#include <limits>
#include <set>

bool arbitraryStart{true}; // Set to false for part 1 and true for part 2

typedef std::array<int, 2> position;
std::vector<std::array<int,2>> directions{{{1,0}, {-1,0}, {0, 1}, {0,-1}}};

std::vector<std::string> ReadLines(std::string fileName){
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

position getPosition(std::vector<std::string>& map, char e) {
    position pos{};
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[r].length(); c++) {
            if (map[r][c] == e) {
                pos = {r,c};
            } 
        } 
    }
    return pos;
}

int getElevation(char elevation) { 
    if (elevation == 'S') {
        elevation = 'a';
    } else if (elevation == 'E') {
        elevation = 'z';
    }
    return elevation;
}

int main() {
    std::vector<std::string> map{ReadLines("map.txt")};
    int numRows{static_cast<int>(map.size())};
    int numColumns{static_cast<int>(map[0].length())};

    int inf{std::numeric_limits<int>::max()};
    std::vector<std::vector<int>> shortestDistance{};
    for (int r = 0; r < numRows; r++) {
        shortestDistance.push_back({});
        for (int c = 0; c < numColumns; c++) {
            shortestDistance[r].push_back(inf);
        }
    }

    position start{getPosition(map, 'S')};
    position goal{getPosition(map, 'E')};
    shortestDistance[start[0]][start[1]] = 0;
    std::set<std::array<int,2>> shortestPathSet{};

    if (arbitraryStart) {
        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < numColumns; c++) {
                if (map[r][c] == 'a') {
                    shortestDistance[r][c] = 0;
                }
            }
        }
    }

    while (true) {
        position vertex{};
        int minDistance{inf};
        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < numColumns; c++) {
                if (shortestPathSet.find({r,c}) != shortestPathSet.end()) { 
                    continue;
                } else if (shortestDistance[r][c] < minDistance) {
                    minDistance = shortestDistance[r][c];
                    vertex = {r,c};
                }
            }
        }
        if (vertex == goal) {
            break;
        }
        shortestPathSet.insert(vertex);
        
        int elevation{getElevation(map[vertex[0]][vertex[1]])};
        for (std::array<int, 2> d : directions) {
            position neighbor{vertex[0] + d[0], vertex[1] + d[1]};
            if (neighbor[0] < 0 || neighbor[0] >= numRows || neighbor[1] < 0 || neighbor[1] >= numColumns){
                continue;
            }
            int neighborElevation{getElevation(map[neighbor[0]][neighbor[1]])};
            if (neighborElevation <= elevation + 1) {
                if (shortestDistance[neighbor[0]][neighbor[1]] > shortestDistance[vertex[0]][vertex[1]] + 1) {
                    shortestDistance[neighbor[0]][neighbor[1]] = shortestDistance[vertex[0]][vertex[1]] + 1;
                }
            }
        }
    }
    std::cout << "Shortest distance to goal is: " << shortestDistance[goal[0]][goal[1]] << std::endl;
    return 0;
}
