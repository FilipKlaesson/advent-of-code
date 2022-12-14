#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stack>
#include <variant>

struct packet : std::vector<std::variant<int,packet>>{ 
    using std::vector<std::variant<int,packet>>::vector;
};

typedef std::vector<packet> packets;

packet ParsePacket(const std::string& line){
    packet p;
    std::stack<packet*> packetStack;
    packetStack.push(&p);

    for(int i = 0; i < line.size(); i++){
        char c = line[i];
        if(c == '['){
            packetStack.push(&std::get<packet>(packetStack.top()->emplace_back(packet{})));
        }else if(c == ']'){
            packetStack.pop();
        }else if(c != ','){
            if(line[i+1] == ',' || line[i+1] == ']'){
                packetStack.top()->push_back(std::stoi(line.substr(i,1)));
            }else if(line[i+2] == ',' || line[i+2] == ']'){
                packetStack.top()->push_back(std::stoi(line.substr(i,2)));
                i++;
            }
        }
    }
    return p;
}

packets ReadPackets(std::string file){
    packets _packets;
    std::ifstream f(file);
    std::string line; 
    while (std::getline(f, line)) {
        if(line.length() != 0){
            _packets.push_back(ParsePacket(line));
        }
    }

    return _packets;
}

template<typename... Ts> 
struct overloaded : Ts... { using Ts::operator()...; };

template<typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

enum result_enum { wrong, correct, equal };

result_enum Compare(const packet& a, const packet& b){
    result_enum result = equal;
    for(int i=0; i<std::max(a.size(),b.size()) && result == equal; ++i){
        if(i == a.size()){
            result = correct;
        }else if(i == b.size()){
            result = wrong;
        }else{
            result = std::visit(overloaded{
                [](const packet& i, const packet& j) { 
                    return Compare(i, j); 
                },
                [](const packet& i, int j) { 
                    return Compare(i, {j}); 
                },
                [](int i, const packet& j) { 
                    return Compare({i}, j); 
                },
                [](int i, int j) {
                    if(i < j){
                        return correct;
                    }else if(i > j){
                        return wrong;
                    }else{
                        return equal;
                    }
                }
            }, a[i], b[i]);
        }
    }
    return result;
}

int main()
{
    packets _packets = ReadPackets("packets.txt");

    int sum = 0;
    for(int i=0; i<_packets.size(); i+=2){
        if(Compare(_packets[i], _packets[i+1])){
            sum += i/2 + 1;
        }
    }
    std::cout << "Index sum of packets in right order: " << sum << std::endl;

    packet d1 = ParsePacket("[[2]]");
    packet d2 = ParsePacket("[[6]]");
    _packets.push_back(d1);
    _packets.push_back(d2);
    std::sort(_packets.begin(), _packets.end(), [](packet& a, packet& b){
        return Compare(a,b);
    });
    auto packetIndex = [&](const packet& p){
        return std::distance(_packets.begin(), std::find(_packets.begin(), _packets.end(), p)) + 1;
    };
    std::cout << "Product of index of decoder keys: " << packetIndex(d1) * packetIndex(d2) << std::endl;
}
