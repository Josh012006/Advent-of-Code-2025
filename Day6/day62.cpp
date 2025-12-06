#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>

class Pair {
public:
    std::string op;
    std::array<int, 2> range;

    Pair(std::string initOp, std::array<int, 2> initRange)
        : op(initOp), range(initRange){}

    bool operator==(const std::string& other) const {
        return this->op == other;
    }
};



std::vector<Pair> specialSplit(std::string text) {
    std::vector<Pair> result;

    std::string toAdd = "";
    int start = 0;
    int n = text.length() - 1;

    for(int i = 0; i <= n; ++i) {
        char c = text[i];
        if(c == ' ') {
            Pair num(toAdd, {start, i-1});
            result.push_back(num);
            toAdd = "";
            start = i+1;
        } else {
            toAdd += c;
        }
    }

    Pair final(toAdd, {start, n});
    result.push_back(final);

    return result;
}


int main() {

    unsigned long long count = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::vector<std::vector<Pair>> lines;
        std::string line;
        int maxLineLength = 0;
        while(std::getline(file, line)) {
            int lineLength = line.length();
            maxLineLength = std::max(maxLineLength, lineLength);
            std::vector<Pair> processedLine = specialSplit(line);
            processedLine.erase(std::remove(processedLine.begin(), processedLine.end(), ""), processedLine.end());
            lines.push_back(processedLine);
        }

        std::vector<Pair> operators = lines.back();

        for(int j = 0; j < operators.size(); j++) {
            int m = lines.size() - 1;
            int n = (j != operators.size() - 1)? operators[j+1].range[0] - operators[j].range[0] - 1 : maxLineLength - operators[j].range[0];
            std::string nums[n];
            for(int i = 0; i < m; ++i) {
                int lwb = operators[j].range[0];
                Pair num = lines[i][j];
                for(int k = 0; k < n; ++k) {
                    std::string toAdd = (k < num.range[0] - lwb || k > num.range[1] - lwb) ? "" : std::string(1, num.op[k - (num.range[0] - lwb)]);
                    nums[k] += toAdd;
                }
            }

            unsigned long long computation = (operators[j] == "+")? 0 : 1;
            for(auto num : nums) {
                if(operators[j] == "+") {
                    computation += std::stoull(num);
                } else {
                    computation *= std::stoull(num);
                }
            }

            count += computation;
        }
    }

    std::cout << count << std::endl;

    return 0;
}