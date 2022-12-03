#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

int GetPriority(char item) {
    return 64 < int(item) && int(item) < 91 ? int(item) - 38 : int(item) - 96;
}

std::tuple<std::string, std::string> GetCompartments(std::string items) {
    int num_items = items.length();
    return {items.substr(0, num_items/2), items.substr(num_items/2)};
}

std::string FindCommon(std::string items1, std::string items2) {
    std::string common{""};
    std::set<char> itemsSet{begin(items1), end(items1)};
    for (char item : items2) {
        if (itemsSet.find(item) != itemsSet.end()) {
            common += item;
        }
    }
    return common;
}

int main() {
    std::ifstream guide("rucksacks.txt");
    std::string rucksack;
    int totalPriority{0};
    int totalGroupPriority{0};
    int groupMembers{0};
    std::string group [3] = {};
    while ( std::getline( guide, rucksack ) ) {
        std::tuple<std::string, std::string> compartments = GetCompartments(rucksack);
        totalPriority += GetPriority(FindCommon(std::get<0>(compartments), std::get<1>(compartments))[0]);
        group[groupMembers] = rucksack;
        groupMembers++;
        if (groupMembers==3){
            groupMembers=0;
            totalGroupPriority += GetPriority(FindCommon(FindCommon(group[0], group[1]), group[2])[0]);
        }
    }
    std::cout << "Total priority: " << totalPriority << std::endl;
    std::cout << "Total group priority: " << totalGroupPriority << std::endl;
    return 0;
}



