#include <iostream>
#include <fstream>
#include <set>
#include <string>


class CustomTuple {
public:
    int val;
    int idx;

    CustomTuple() : val(0), idx(0) {};
    CustomTuple(int value, int index)
        : val(value), idx(index) {}

    bool operator<(const CustomTuple other) const {
        if(this->val != other.val) return this->val > other.val;
        return this->idx < other.idx;
    }
};


int main() {

    int sum = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::string line;
        while(std::getline(file, line)) {
            std::set<CustomTuple> elements;

            for(int i = 0; i < line.length(); i++) {
                CustomTuple battery(line[i] - '0', i);
                elements.insert(battery);
            }

            CustomTuple fst;
            CustomTuple snd;

            for(CustomTuple bat : elements) {
                if(bat.idx != line.length() - 1) {
                    fst = bat;
                    elements.erase(bat);
                    break;
                }
            }

            for(CustomTuple bat : elements) {
                if(bat.idx > fst.idx) {
                    snd = bat; break;
                }
            }
            sum += fst.val * 10 + snd.val;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}