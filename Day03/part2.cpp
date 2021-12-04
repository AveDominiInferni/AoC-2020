#include <iostream>
#include <fstream>
#include <vector>

unsigned long long int count_trees(const std::vector <std::string> &terrain, unsigned int x_step, unsigned int y_step) {
    std::size_t x = 0, y = 0;
    unsigned long long int counter = 0;
    while (y < terrain.size()) {
        if (x >= terrain.at(0).length())
            x -= terrain.at(0).length();
        if (terrain.at(y).at(x) == '#')
            counter++;
        y += y_step;
        x += x_step;
    }
    return counter;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector <std::string> terrain;
        std::string line;
        while (std::getline(file, line))
            terrain.push_back(line);
        std::cout << count_trees(terrain, 1, 1) * count_trees(terrain, 3, 1) * count_trees(terrain, 5, 1) 
            * count_trees(terrain, 7, 1) * count_trees(terrain, 1, 2);
    }
    file.close();
    return 0;
}
