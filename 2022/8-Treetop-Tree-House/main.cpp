#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> ReadLines(std::string fileName){
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main() {
    std::vector<std::string> grid{ReadLines("grid.txt")};
    int numRows{static_cast<int>(grid.size())};
    int numColumns{static_cast<int>(grid[0].length())};
    int numVisible{0};
    int maxScore{0};
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numColumns; column++) {
            bool visible{false};
            int score{1};
            for (std::array<int,2> direction: std::vector<std::array<int, 2>>{{1,0}, {-1,0}, {0, 1}, {0,-1}}) {
                int dist{0};
                int _row = row;
                int _column = column;
                while (true){
                    _row += direction[0];
                    _column += direction[1];
                    if (_row < 0 || _row > numRows -1 || _column < 0 || _column > numColumns - 1 ) {
                        visible = true;
                        break;
                    }
                    dist += 1;
                    if (grid[_row][_column] >= grid[row][column]) {
                        break;
                    }
                }
                score *= dist;
            }
            if (visible) {
                numVisible += 1;
            }
            if (score > maxScore){
                maxScore = score;
            }
        }
    }
    std::cout << "Number of visible trees: " << numVisible << std::endl;
    std::cout << "Max score: " << maxScore << std::endl;
    return 0;
}
