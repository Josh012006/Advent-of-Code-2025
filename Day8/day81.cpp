#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <array>
#include <algorithm>
#include <limits>



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

class Vertex3 {
public:
    Vertex3() : x(0), y(0), z(0){};
    Vertex3(unsigned long long xi, unsigned long long yi, unsigned long long zi) : x(xi), y(yi), z(zi) {};

    unsigned long long x, y, z;

    static unsigned long long dist2(Vertex3 p1, Vertex3 p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
    }

    bool operator==(Vertex3 const& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }
};

class Circuit {
public:
    Circuit() {}
    Circuit(Vertex3 initVal, int idx) : uniqueKey(idx) {
        std::vector<Vertex3> blank; blank.push_back(initVal);
        this->content = blank;
    }
    Circuit(std::vector<Vertex3> toJoin1, std::vector<Vertex3> toJoin2, int idx) : uniqueKey(idx) {
        this->content = toJoin1;
        for(auto v : toJoin2) { this->content.push_back(v); }
    }

    std::vector<Vertex3> content;
    int uniqueKey;

    bool operator<(Circuit const& other) const {
        if(this->content.size() != other.content.size()) return this->content.size() > other.content.size();
        return this->uniqueKey > other.uniqueKey;
    }
    void add(Vertex3 newV) { this->content.push_back(newV); }
    bool contains(Vertex3 const v) const {
        return std::find(content.begin(), content.end(), v) != content.end();
    }
};


std::vector<std::vector<unsigned long long>> distMatrix(std::vector<Vertex3> vertices) {
    int n = vertices.size();
    std::vector<std::vector<unsigned long long>> m(
            n,
            std::vector<unsigned long long>(n, 0)
    );

    for (int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            m[i][j] = Vertex3::dist2(vertices[i], vertices[j]);
        }
    }

    return m;
}


bool notConnected(Vertex3 v1, Vertex3 v2, std::set<Circuit>& circuits, Circuit (&result)[2]) {

    std::set<Circuit>::iterator it1 = circuits.end();
    std::set<Circuit>::iterator it2 = circuits.end();

    for(auto it = circuits.begin(); it != circuits.end(); ++it) {
        if(it->contains(v1)) {
            it1 = it;
        }

        if(it->contains(v2)) {
            it2 = it;
        }
    }

    if(it1 != circuits.end() && it2 != circuits.end() && it1 != it2) {
        result[0] = *it1; result[1] = *it2;
        return true;
    }
    return false;
}


int main() {


    std::ifstream file("test.txt");
    if(file.good()) {

        // Extract the junction boxes positions
        std::string line;
        std::vector<Vertex3> vertices;
        while (std::getline(file, line)) {
            std::vector<std::string> components = split(line, ',');
            Vertex3 v(std::stoull(components[0]), std::stoull(components[1]), std::stoull(components[2]));
            vertices.push_back(v);
        }

        auto matrix = distMatrix(vertices);

        std::set<Circuit> circuits;
        // Initialize circuits
        for(int i = 0; i < vertices.size(); ++i) {
            Vertex3 v = vertices[i];
            Circuit init(v, i); circuits.insert(init);
        }

        bool change;
        int numConnect = 0;

        do {
            change = false;
            unsigned long long minDist = std::numeric_limits<unsigned long long>::max();
            Circuit toConnect[2];

            int n = matrix.size();

            for (int i = 0; i < n; ++i) {
                for(int j = i + 1; j < n; ++j) {
                    Circuit res[2];
                    if(notConnected(vertices[i], vertices[j], circuits, res) && matrix[i][j] < minDist) {
                        minDist = matrix[i][j];
                        toConnect[0] = res[0];
                        toConnect[1] = res[1];
                        change = true;
                    }
                }
            }

            if(change) {
                std::cout << "Connecting circuits of sizes "
                          << toConnect[0].content.size() << " and "
                          << toConnect[1].content.size() << std::endl;

                Circuit toInsert(toConnect[0].content, toConnect[1].content, toConnect[0].uniqueKey);
                circuits.erase(toConnect[0]); circuits.erase(toConnect[1]);
                circuits.insert(toInsert);
            }

            ++numConnect;

        } while(numConnect <= 10);

        std::cout << "Right now there are " << circuits.size() << " circuits." << std::endl;

        for(auto it = circuits.begin(); it != circuits.end(); ++it) {
            std::cout << "There is one circuit of size " << it->content.size() << std::endl;
        }

        int result = 1;
        int seen = 1;
        for(auto it = circuits.begin(); it != circuits.end() && seen <= 3; ++it) {
            std::cout << "Multiplied circuit of size" << it->content.size() << std::endl;
            result *= it->content.size(); ++seen;
        }

        std::cout << result << std::endl;

    }


    return 0;
}