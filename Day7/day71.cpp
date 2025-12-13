#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>




int main() {

    int countSplit = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::string line;
        std::vector<std::string> lines;
        while(std::getline(file, line)) {
            lines.push_back(line);
        }

        std::string first = lines.front();
        size_t pos = first.find('S');


        if(pos != std::string::npos) {
            std::set<int> prevPos;
            prevPos.insert(pos);

            for(int j = 1; j < lines.size(); j++) {
                std::string l = lines[j];
                std::vector<int> toAdd;
                std::vector<int> toRemove;

                for(int i : prevPos) {
                    if(l[i] == '^') {
                        toRemove.push_back(i);
                        countSplit++;
                        if(i != 0) {
                            toAdd.push_back(i - 1);
                        }
                        if(i != l.length() - 1) {
                            toAdd.push_back(i + 1);
                        }
                    }
                }

                for(int elem : toAdd) {
                    prevPos.insert(elem);
                }
                for(int elem : toRemove) {
                    prevPos.erase(elem);
                }
            }
        }
    }

    std::cout << countSplit << std::endl;


    return 0;
}