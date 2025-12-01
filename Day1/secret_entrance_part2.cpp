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
            int offset;
            if(direction == 'R') {
                offset = position + distance;
                newPos = offset % 100;

                count += newPos < position;
            } else {
                offset = position - distance;
                newPos = offset % 100;
                newPos += (newPos < 0) ? 100 : 0;

                count += (newPos > position) || (newPos < position && newPos == 0);
            }

            count += distance / 100;

            position = newPos;
        }
    }

    std::cout << count << std::endl;

    return 0;
}
