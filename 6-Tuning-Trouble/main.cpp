#include <fstream>
#include <iostream>
#include <string>
#include <set>


int MessageStartIndex(std::string &signal, int markerSize) {
    int startIndex;
    for (int i = 0; i < signal.length() - markerSize; i++) {
        std::string marker = signal.substr(i, markerSize);
        std::set<char> markerSet;
        for (char m : marker) {
            markerSet.insert(m);
        }
        if (markerSet.size() == markerSize) {
            startIndex = i + markerSize;
            break;
        }
    }
    return startIndex;
}

int main() {
    std::ifstream buffer("buffer.txt");
    std::string signal;
    getline(buffer, signal);
    std::cout << "Start index 1: " << MessageStartIndex(signal, 4) << std::endl;
    std::cout << "Start index 2: " << MessageStartIndex(signal, 14) << std::endl;
    return 0;
}