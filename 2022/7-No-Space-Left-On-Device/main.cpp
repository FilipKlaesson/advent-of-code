#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <filesystem>
namespace fs = std::filesystem;

int totalSpace{70000000};
int spaceRequired{30000000};

std::vector<std::string> ReadLines(std::string fileName){
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> Split(std::string string) {
    const char* delimiter{" "};
    std::vector<std::string> tokens{};
    char * token = std::strtok((char*)string.c_str(), delimiter);
    while (token != nullptr) {
        tokens.push_back(std::string(token));
        token = strtok(nullptr, delimiter);
    }
    return tokens;
}

void ChangeDirectory(fs::path &path, std::string cd) {
    if (cd == "/") {
        path = "/";
    } else if (cd == "..") {
        path = path.parent_path();
    } else {
        path /= cd;
    }
    return;
}

void AddSizeRecursive(std::map<std::string,int> &dirSize, fs::path path, int size) {
    dirSize[path.string()] += size;
    if (path.has_relative_path()) {
        AddSizeRecursive(dirSize, path.parent_path(), size);
    }
}

int main() {
    std::vector<std::string> terminal{ReadLines("terminal.txt")};
    std::map<std::string,int> dirSize;

    fs::path wd;
    for (std::string line : terminal) {
        std::vector<std::string> parts{Split(line)};
        if (parts[1] == "ls") {
            continue;
        } else if (parts[1] == "cd") {
            ChangeDirectory(wd, parts[2]);
            if (dirSize.find(wd.string()) == dirSize.end()) {
                dirSize[wd.string()] = 0;
            }
        } else if (parts[0] == "dir") {
            continue;
        } else {
            AddSizeRecursive(dirSize, wd, std::stoi(parts[0]));
        }
    }


    int sizeSum{0};
    int deleteSpace{dirSize["/"]};
    int minDeleteSpace{spaceRequired - (totalSpace - dirSize["/"])};
    for (auto const& [dir, size] : dirSize) {
        if (size <= 100000) {
            sizeSum += size;
        }
        if (size >= minDeleteSpace && size < deleteSpace) {
            deleteSpace = size;
        }
    }
    std::cout << "Sum of diretory sizes: "<< sizeSum << std::endl;
    std::cout << "Size of diretory to delete: "<< deleteSpace << std::endl;
    return 0;
}