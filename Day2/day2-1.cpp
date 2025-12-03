#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

std::vector<std::string> split(std::string text, char delim) {
    std::vector<std::string> result;

    std::string toAdd = "";

    for(char c : text) {
        if(c == delim) {
            result.push_back(toAdd);
            toAdd = "";
        } else {
            toAdd += c;
        }
    }

    result.push_back(toAdd);
    return result;
}

int main() {

    std::ifstream file("input.txt");
    if(file.good()) {
        std::string line;
        std::getline(file, line);

        std::uint64_t invalidSum = 0;

        std::vector<std::string> ranges = split(line, ',');
        for(auto s : ranges) {
            std::vector<std::string> bounds = split(s, '-');
            std::uint64_t lower = std::stoull(bounds[0]); std::uint64_t upper = std::stoull(bounds[1]);

            for(auto i = lower; i <= upper; i++) {
                std::string i_text = std::to_string(i);
                if(i_text.length() % 2 == 0 && i_text.substr(0, i_text.length()/2) == i_text.substr(i_text.length()/2)) {
                    invalidSum += i;
                }
            }
        }

        std::cout << invalidSum << std::endl;
    }

    return 0;
}