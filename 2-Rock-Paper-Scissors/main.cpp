#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <iterator>
#include <map>

std::map<char, int> actionScore{{'X', 1},{'Y', 2},{'Z', 3}};
std::map<std::tuple<char, char>, int> gameScore{
    {{'A', 'X'}, 3}, {{'A', 'Y'}, 6}, {{'A', 'Z'}, 0},
    {{'B', 'X'}, 0}, {{'B', 'Y'}, 3}, {{'B', 'Z'}, 6},
    {{'C', 'X'}, 6}, {{'C', 'Y'}, 0}, {{'C', 'Z'}, 3},
};
std::map<std::tuple<char, char>, char> getAction{
    {{'A', 'X'}, 'Z'}, {{'A', 'Y'}, 'X'}, {{'A', 'Z'}, 'Y'},
    {{'B', 'X'}, 'X'}, {{'B', 'Y'}, 'Y'}, {{'B', 'Z'}, 'Z'},
    {{'C', 'X'}, 'Y'}, {{'C', 'Y'}, 'Z'}, {{'C', 'Z'}, 'X'},
};

int main()
{
    std::ifstream guide("guide.txt");
    std::string line;
    int score1{0};
    int score2{0};
    while ( std::getline( guide, line ) ) {
        char opponentAction = line.at(0);
        char action1 = line.at(2);
        char result = line.at(2);
        // Part 1
        score1 += actionScore[action1] + 
            gameScore[std::tuple<char, char>{ opponentAction, action1 }];
        // Part 2
        char action2 = getAction[std::tuple<char, char>{ opponentAction, result }];
        score2 += actionScore[action2] + 
            gameScore[std::tuple<char, char>{ opponentAction, action2 }];
    }
    std::cout << "Total guide score part 1: " << score1 << std::endl;
    std::cout << "Total guide score part 2: " << score2 << std::endl;
    return 0;
}



