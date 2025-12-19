#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <array>



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
        return this->x == other->x && this->y == other->y && this->z == other->z;
    }
};

class Circuit {
public:
    Circuit() {}
    Circuit(Vertex3 initVal) {
        std::vector<Vertex3> blank; blank.push_back(initVal);
        this->content = blank;
    }
    Circuit(std::vector<Vertex3> init) {
        this->content = init;
    }
    Circuit(std::vector<Vertex3> toJoin1, std::vector<Vertex3> toJoin2) {
        this->content = toJoin1;
        for(auto v : toJoin2) { this->content.push_back(v) };
    }

    std::vector<Vertex3> content;

    bool operator<(Circuit const& other) const {
        return this->content.size() < other->content.size();
    }
    void add(Vertex3 newV) { this->content.push_back(newV); }
    bool contains(Vertex3 const v) const {
        return content.find(content.begin(), content.end(), v) != content.end();
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


bool notConnected(Vertex3 v1, Vertex3 v2, std::set<Circuit> circuits, Circuit (&result)[2]) {
    Circuit cv1, cv2;
    auto it1, it2;
    for(auto it = circuits.begin(); it != circuits.end(); ++it) {
        if(*it->content.find(v1) != *it->content.end()) {
            it1 = it; cv1 = *it;
        }

        if(*it->content.find(v2) != *it->content.end()) {
            it2 = it; cv2 = *it;
        }
    }

    if(it1 != it2) {
        result[0] = cv1; result[1] = cv2;
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
        for(Vertex3 v : vertices) {
            Circuit init(v); circuits.insert(init);
        }

        bool change;

        do {
            change = false;
            unsigned long long minDist = std::numeric_limits<unsigned long long>::max();
            Circuit toConnect[2];

            for (int i = 0; i < n; ++i) {
                for(int j = i + 1; j < n; ++j) {
                    if(matrix[i][j] <= minDist && notConnected(vertices[i], vertices[j], circuits, toConnect)) {
                        change = true;
                    }
                }
            }

            if(change) {
                Circuit toInsert(toConnect[0].content, toConnect[1].content);
                circuits.erase(toConnect[0]); circuits.erase(toConnect[1]);
                circuits.insert(toInsert);
            }

        } while(change)

        int result = 1;
        int seen = 0;
        for(auto it = circuits.begin(); it != circuits.end() && seen <= 3; ++it) {
            result *= *it; ++seen;
        }

        return result;

    }


    return 0;
}