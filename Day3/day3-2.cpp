#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <cmath>
#include <cstdint>

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

    friend std::ostream& operator<<(std::ostream& os, const CustomTuple& elem) {
        os << "(" << elem.val << ", " << elem.idx << ")";
        return os;
    }
};


int main() {

    std::uint64_t sum = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::string line;
        while(std::getline(file, line)) {
            std::set<CustomTuple> elements;

            for(int i = 0; i < line.length(); i++) {
                CustomTuple battery(line[i] - '0', i);
                elements.insert(battery);
            }

            CustomTuple tab[12];
            for(int i = 0; i < 12; i++) {
                for(CustomTuple bat : elements) {
                    if((i == 0 || bat.idx > tab[i-1].idx) && bat.idx < line.length() - 11 + i) {
                        tab[i] = bat;
                        elements.erase(bat);
                        break;
                    }
                }
            }

            for(int i = 0; i < 12; i++) {
                sum += tab[i].val * std::pow(10, 11 - i);
            }


        }
    }

    std::cout << sum << std::endl;

    return 0;
}