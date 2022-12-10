#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main()
{
    std::ifstream calories("calories.txt");
    std::string line;
    std::vector<int> total{0};
    while ( getline( calories, line ) ) {
        if (line == "") {
            total.push_back( 0 );
        } else {
            total.back() = total.back() + std::stoi( line );
        }
    }

    std::sort(total.begin(), total.end(), std::greater<int>());
    std::cout << "Most calories: " << total.front() << std::endl;
    std::cout << "Top 3 most calories: " << std::accumulate( total.begin(), total.begin()+3, 0 ) << std::endl;

    return 0;
}

