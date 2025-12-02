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

            count += distance / 100;
            int offset = distance % 100;

            if(direction == 'R') {
                newPos = (position + offset) % 100;
                count += newPos < position;
            } else {
                newPos = position - offset;
                newPos += (newPos < 0) ? 100 : 0;

                count += (newPos > position) || (newPos < position && newPos == 0);
            }

            position = newPos;
        }
    }

    std::cout << count << std::endl;

    return 0;
}
