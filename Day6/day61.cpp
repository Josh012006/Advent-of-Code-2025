#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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


int main() {

    unsigned long long count = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::vector<std::vector<std::string>> lines;
        std::string line;
        while(std::getline(file, line)) {
            std::vector<std::string> processedLine = split(line, ' ');
            processedLine.erase(std::remove(processedLine.begin(), processedLine.end(), ""), processedLine.end());
            lines.push_back(processedLine);
        }

        std::vector<std::string> operators = lines.back();

        for(int j = 0; j < operators.size(); j++) {
            unsigned long long computation = (operators[j] == "+")? 0 : 1;
            for(int i = 0; i < lines.size() - 1; i++) {
                if(operators[j] == "+") {
                    computation += std::stoull(lines[i][j]);
                } else {
                    computation *= std::stoull(lines[i][j]);
                }
            }
            count += computation;
        }
    }

    std::cout << count << std::endl;

    return 0;
}