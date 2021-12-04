#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector <std::string> terrain;
        std::string line;
        std::size_t x = 0, y = 0;
        unsigned int counter = 0;
        while (std::getline(file, line))
            terrain.push_back(line);
        while (y < terrain.size()) {
            if (x >= terrain.at(0).length())
                x -= terrain.at(0).length();
            if (terrain.at(y).at(x) == '#')
                counter++;
            y++;
            x += 3;
        }
        std::cout << counter << std::endl;
    }
    file.close();
    return 0;
}
