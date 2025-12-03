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

bool is_n_repetition(std::string text, int n) {
    std::string value = text.substr(0, n);
    for(int i = n; i <= text.length() - n; i += n) {
        if(text.substr(i, n) != value) return false;
    }
    return true;
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
                for(int n = i_text.length() / 2; n >= 1; n--) {
                    if(i_text.length() % n == 0 && is_n_repetition(i_text, n)) {
                        invalidSum += i;
                        break;
                    }
                }
            }
        }

        std::cout << invalidSum << std::endl;
    }

    return 0;
}