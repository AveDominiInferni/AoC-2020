#include <iostream>
#include <fstream>
#include <deque>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::deque<unsigned long long> d;
        for (int i = 0; i < 25 ; i++) {
            std::getline(file, line);
            d.push_back(std::stoull(line));
        }
        while (std::getline(file, line)) {
            unsigned long long number = std::stoull(line);
            bool found = false;
            for (int i = 0; i < d.size() - 1; i++) {
                for (int j = 0; j < d.size(); j++) {
                    if (d.at(i) + d.at(j) == number) {
                        d.pop_front();
                        d.push_back(number);
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }
            if (!found) {
                std::cout << number;
                break;
            }
        }
    }
    file.close();
    return 0;
}