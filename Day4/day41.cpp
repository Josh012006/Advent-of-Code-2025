#include <iostream>
#include <string>
#include <fstream>
#include <vector>




int main() {

    int count = 0;

    std::ifstream file("input.txt");
    if(file.good()) {
        std::vector<std::string> lines;
        std::string line;
        while(std::getline(file, line)) {
            lines.push_back(line);
        }

        int m = lines.size();
        int n = (lines.size() == 0)? 0 : lines[0].length();  // always good to make sure the file isn't empty :)

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                char target = lines[i][j];
                if(target == '@') {
                    int okay = 0;
                    okay += (i == 0 || j == 0 || lines[i-1][j-1] == '.');
                    okay += (i == 0 || lines[i-1][j] == '.');
                    okay += (i == 0 || j == n-1 || lines[i-1][j+1] == '.');
                    okay += (j == 0 || lines[i][j-1] == '.');
                    okay += (j == n-1 || lines[i][j+1] == '.');
                    okay += (i == m-1 || j == 0 || lines[i+1][j-1] == '.');
                    okay += (i == m-1 || lines[i+1][j] == '.');
                    okay += (i == m-1 || j == n-1 || lines[i+1][j+1] == '.');

                    count += (okay > 4);
                }
            }
        }

    }

    std::cout << count << std::endl;


    return 0;
}