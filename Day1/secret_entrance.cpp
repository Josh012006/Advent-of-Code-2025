#include <iostream>
#include <fstream>
#include <string>

int main() {

    int count = 0;
    int position = 50;

    // Lecture de l'input
    std::ifstream input("input.txt");
    if(input.good()) {
        std::string line;
        while(std::getline(input, line)) {
            char direction = line[0];
            int distance = std::stoi(line.substr(1));

            int newPos;
            if(direction == 'R') {
                newPos = (position + distance) % 100;
            } else {
                newPos = ((position - distance) % 100);
                newPos += (newPos < 0) ? 100 : 0;
            }

            position = newPos;
            if (newPos == 0) count++;
        }
    }

    std::cout << count << std::endl;

    return 0;
}
