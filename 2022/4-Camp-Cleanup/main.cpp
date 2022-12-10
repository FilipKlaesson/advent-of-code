#include <fstream>
#include <iostream>
#include <string>
#include <regex>

std::regex rx("^(\\d+)-(\\d+),(\\d+)-(\\d+)$");

bool AnyOverlap(int min1, int max1, int min2, int max2) {
    if ((max1 >= min2 && min1 <= max2) || (max2 >= min1 && min2 <= max1)) {
        return true;
    }
    return false;
}

bool FullOverlap(int min1, int max1, int min2, int max2) {
    if ((min1 >= min2 && max1 <= max2) || (min2 >= min1 && max2 <= max1) ) {
        return true;
    }
    return false;
}

int main() {
    std::ifstream sections("sections.txt");
    std::string pair;
    int numFullOverlaps(0);
    int numAnyOverlaps(0);
    while ( std::getline( sections, pair ) ) {
        std::smatch matches;
        std::regex_search(pair, matches, rx);
        int bounds [4] = {
            std::stoi(matches[1].str()), std::stoi(matches[2].str()), 
            std::stoi(matches[3].str()), std::stoi(matches[4].str())
        };
        numFullOverlaps += FullOverlap(bounds[0],bounds[1],bounds[2],bounds[3]);
        numAnyOverlaps += AnyOverlap(bounds[0],bounds[1],bounds[2],bounds[3]);
    }
    std::cout << "Number of full overlaps: " << numFullOverlaps << std::endl;
    std::cout << "Number of any overlaps: " << numAnyOverlaps << std::endl;
    return 0;
}
