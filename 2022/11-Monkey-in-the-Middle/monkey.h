#include <string>
#include <array>
#include <vector>

class Monkey {
    private:
        std::vector<int> items;
        std::vector<std::string> operation;
        int testDenominator;
        int testTrue;
        int testFalse;
        int numInspects = 0;
    public:
        Monkey(
            std::vector<int> startingItems,
            std::vector<std::string> operation,
            int testDenominator,
            int testTrue,
            int testFalse
        );
        std::vector<std::array<long,2>> Throw(int leastCommonMultiple = 0);
        void Catch(long item);
        int NumInspects();
};
