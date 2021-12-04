#include <iostream>
#include <set>
#include <fstream>

class coordinate {
public:
    int8_t x, y, z;
    bool operator <(const coordinate& c) const {
        if (x < c.x)
            return true;
        if (x == c.x && y < c.y)
            return true;
        if (x == c.x && y == c.y && z < c.z)
            return true;
        return false;
    }
};

class convay_cube {
    std::set<coordinate> active;
public:
    uint32_t size() { return active.size(); }
    void add(int8_t x, int8_t y, int8_t z) { active.insert(coordinate({x, y, z})); }
    void erase(int8_t x, int8_t y, int8_t z) { active.erase(coordinate({x, y, z})); }
    std::set<coordinate> get_neigbhours(int8_t x, int8_t y, int8_t z) {
        std::set<coordinate> temp;
        for (int8_t i = x - 1; i <= x + 1; i++)
            for (int8_t j = y - 1; j <= y + 1; j++)
                for (int8_t k = z - 1; k <= z + 1; k++) 
                    temp.insert(coordinate({i, j, k}));
        temp.erase(coordinate({x, y, z}));
        return temp;
    }
    uint32_t active_neighbours(int8_t x, int8_t y, int8_t z) {
        uint32_t count = 0;
        std::set<coordinate> temp(get_neigbhours(x, y, z));
        for (coordinate coord : temp) {
            auto it = active.find(coordinate({coord.x, coord.y, coord.z}));
            if (it != active.end())
                count++;
        }
        return count;
    }
    void cycle(uint8_t n) {
        for (int i = 0; i < n; i++) {
            std::set<coordinate> next_cycle;
            std::set<coordinate> coords_to_check;
            for (coordinate coord : active) {
                std::set<coordinate> temp = get_neigbhours(coord.x, coord.y, coord.z);
                coords_to_check.insert(temp.begin(), temp.end());
            }
            for (coordinate coord : coords_to_check) {
                auto count = active_neighbours(coord.x, coord.y, coord.z);
                auto it = active.find(coord);
                if (it != active.end() && (count == 2 || count == 3))
                    next_cycle.insert(coord);
                else if (count == 3)
                    next_cycle.insert(coord);
            }

            active = next_cycle;
        }
    }
};

int main() {
    convay_cube c;
    std::ifstream file("input.txt");
    std::string line;
    int i = 0;
    while(std::getline(file, line)) {
        for (int j = 0; j < line.size(); j++)
            if (line.at(j) == '#')
                c.add(i, j, 0);
        i++;
    }
    c.cycle(6);
    std::cout << c.size() << std::endl;
}