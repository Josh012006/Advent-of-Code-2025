#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <algorithm>



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


void sanitize(std::set<std::array<unsigned long long, 2>>& elems) {
    bool changed;

    do{
        changed = false;
        for (auto it = elems.begin(); it != elems.end(); ++it) {
            auto& elem = *it;
            auto nextIt = std::next(it);
            if (nextIt != elems.end()) {
                auto& nextElem = *nextIt;

                auto lower1 = elem[0];
                auto upper1 = elem[1];

                auto lower2 = nextElem[0];
                auto upper2 = nextElem[1];

                if(lower1 == lower2 || upper1 >= lower2) {
                    std::array<unsigned long long, 2> toInsert = {lower1, std::max(upper1, upper2)};
                    elems.erase(elem); elems.erase(nextElem);
                    elems.insert(toInsert);
                    changed = true;
                    break;
                }
            }
        }
    } while(changed);
}


int main() {

    unsigned long long count = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::string line;
        std::set<std::array<unsigned long long, 2>> ranges;

        // Reading the input and separating the values
        while(std::getline(file, line)) {
            if(line.empty()) {
                break;
            } else {
                std::vector<std::string> bounds = split(line, '-');
                unsigned long long lower = std::stoull(bounds[0]);
                unsigned long long upper = std::stoull(bounds[1]);
                ranges.insert({lower, upper});
            }
        }

        // Sanitize the set
        sanitize(ranges);

        // Final computation
        for(auto range : ranges) {
            count += range[1] - range[0] + 1;
        }

    }


    std::cout << count << std::endl;

    return 0;
}