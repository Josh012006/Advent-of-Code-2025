#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

std::vector<std::string> lines;
std::map<std::string, unsigned long long> cache;

unsigned long long evaluate(int beamPrevPos, int line) {
    std::string key = std::to_string(beamPrevPos) + "-" + std::to_string(line);
    if(cache.find(key) != cache.end()) {
        return cache[key];
    }

    if(line == lines.size() - 1) {
        return 1;
    }

    std::string l = lines[line];

    unsigned long long value;

    if(l[beamPrevPos] == '^') {
        value = ((beamPrevPos == 0) ? 0 : evaluate(beamPrevPos - 1, line + 1)) +
        ((beamPrevPos == l.length() - 1) ? 0 : evaluate(beamPrevPos + 1, line + 1));
    } else {
        value = evaluate(beamPrevPos, line + 1);
    }

    cache[key] = value;
    return value;
}


int main() {

    unsigned long long countSplit = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::string line;
        while(std::getline(file, line)) {
            lines.push_back(line);
        }

        std::string first = lines.front();
        size_t pos = first.find('S');

        if(pos != std::string::npos) {
            countSplit = evaluate(pos, 1);
        }
    }

    std::cout << countSplit << std::endl;


    return 0;
}
