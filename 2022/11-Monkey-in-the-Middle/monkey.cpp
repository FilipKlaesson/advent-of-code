#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "monkey.h"

Monkey::Monkey(
    std::vector<int> startingItems,
    std::vector<std::string> _operation,
    int _testDenominator,
    int _testTrue,
    int _testFalse
) {
    items = startingItems;
    operation = _operation;
    testDenominator = _testDenominator;
    testTrue = _testTrue;
    testFalse = _testFalse;
}

std::vector<std::array<long,2>> Monkey::Throw(int leastCommonMultiple) {
    std::vector<std::array<long,2>> throws{};
    for (long item : items) {
        numInspects++;
        
        long o1{};
        if (operation[0] == "old") {
            o1 = item;
        } else {
            o1 = std::stoi(operation[0]);
        }
        
        long o2{};
        if (operation[2] == "old") {
            o2 = item;
        } else {
            o2 = std::stoi(operation[2]);
        }

        if (operation[1] == "*"){
            item = o1 * o2;
        } else if (operation[1] == "+") {
            item = o1 + o2;
        }

        if (leastCommonMultiple != 0) {
            item %= leastCommonMultiple;
        } else {
            item /= 3;
        }

        int catcher{};
        if (item % testDenominator == 0) {
            catcher = testTrue;
        } else {
            catcher = testFalse;
        }     
        throws.push_back({item, catcher});
    }
    items.clear();
    return throws;
}

void Monkey::Catch(long item) {
    items.push_back(item);
}

int Monkey::NumInspects() {
    return numInspects;
}
