#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<int> v;
        std::string line1, line2;
        std::getline(file, line1);
        std::getline(file, line2);
        int ts = std::stoi(line1);
        std::stringstream ss(line2);
        std::string field;
        while (std::getline(ss, field, ',')) {
            if (field == "x")
                continue;
            v.push_back(std::stoi(field));
        }
        file.close();

        for (int wait = 0; wait < ts; wait++) {
            for (int i = 0; i < v.size(); i++) {
                if ((ts + wait) % v.at(i) == 0) {
                    std::cout << wait * v.at(i);
                    return 0;
                }
            }
        }
    }
    return 1;
}