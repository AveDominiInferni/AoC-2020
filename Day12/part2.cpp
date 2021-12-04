#include <iostream>
#include <fstream>
#include <vector>

void turn(std::pair<int, int> &wp, int deg) {
    int turns = deg / 90;
    if (turns < 0)
        turns += 4;
    while (turns != 0) {
        std::swap(wp.first, wp.second);
        wp.second = -wp.second;
        turns--;
    }
}

void move(std::pair<int, int> &p, const std::pair<int, int> &wp, int f = 1) {
    p.first += f * wp.first;
    p.second += f * wp.second;
}

int main() {
    std::ifstream file("input.txt");
    std::pair<int, int> position(0, 0);
    std::pair<int, int> waypoint(10, 1);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            char command = line.at(0);
            int num = std::stoi(line.substr(1));
            if (command == 'R')
                turn(waypoint, num);
            else if (command == 'L')
                turn(waypoint, -num);
            else if (command == 'F')
                move(position, waypoint, num);
            else if (command == 'N')
                move(waypoint, {0, num});
            else if (command == 'E')
                move(waypoint, {num, 0});
            else if (command == 'S')
                move(waypoint, {0, -num});
            else if (command == 'W')
                move(waypoint, {-num, 0});
            //std::cout << position.first << " " << position.second << " " << waypoint.first << " " << waypoint.second << std::endl;
        }
        std::cout << abs(position.first) + abs(position.second) << std::endl;
    }
    file.close();
    return 0;
}