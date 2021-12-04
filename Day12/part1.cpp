#include <iostream>
#include <fstream>
#include <vector>

enum class dir{ 
    north, //0
    east,  //1
    south, //2
    west  //3
};

void turn(dir &d, int deg) {
    int turns = deg / 90;
    if (turns < 0)
        turns += 4;
    d = static_cast<dir>((static_cast<int>(d) + turns) % 4);
}
void move(std::pair<int, int> &p, dir d, int dist) {
    if (d == dir::north)
        p.second += dist;
    else if (d == dir::east)
        p.first += dist; 
    else if (d == dir::south)
        p.second -= dist;
    else if (d == dir::west)
        p.first -= dist; 
}

int main() {
    std::ifstream file("input.txt");
    std::pair<int, int> position(0, 0);
    dir d = dir::east;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            char command = line.at(0);
            int num = std::stoi(line.substr(1));
            if (command == 'R')
                turn(d, num);
            else if (command == 'L')
                turn(d, -num);
            else if (command == 'F')
                move(position, d, num);
            else if (command == 'N')
                move(position, dir::north, num);
            else if (command == 'E')
                move(position, dir::east, num);
            else if (command == 'S')
                move(position, dir::south, num);
            else if (command == 'W')
                move(position, dir::west, num);
        }
        std::cout << abs(position.first) + abs(position.second) << std::endl;
    }
    file.close();
    return 0;
}