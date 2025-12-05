#include <iostream>
#include <fstream>
#include <string>
#include <vector>



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

    int count = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::string line;
        std::vector<std::string> ranges;
        std::vector<std::string> values;

        bool readingValues = false;

        // Reading the input and separating the values
        while(std::getline(file, line)) {
            if(line.empty()) {
                readingValues = true;
            } else if(readingValues) {
                values.push_back(line);
            } else {
                ranges.push_back(line);
            }
        }

        for(std::string val : values) {
            unsigned long long intVal = std::stoull(val);

            for(std::string range : ranges) {
                std::vector<std::string> bounds = split(range, '-');
                unsigned long long lower = std::stoull(bounds[0]);
                unsigned long long upper = std::stoull(bounds[1]);

                if(intVal >= lower && intVal <= upper) {
                    count++; break;
                }
            }
        }

    }


    std::cout << count << std::endl;


    return 0;
}