#include <iostream>
#include <fstream>
#include <set>

int get_id(const std::string &s) {
    int lowerR = 0, upperR = 128;
    int lowerC = 0, upperC = 8;
    int half = 0;
    for (char c : s) {
        if (c == 'F') {
            upperR -= (upperR - lowerR) / 2;
        }
        else if (c == 'B') {
            lowerR += (upperR - lowerR) / 2;
        }
        else if (c == 'R') {
            lowerC += (upperC - lowerC) / 2;
        }
        else if (c == 'L') {
            upperC -= (upperC - lowerC) / 2;
        }
    }
    return lowerR * 8 + lowerC;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::set<int> s;
        while (std::getline(file, line)) {
            s.insert(get_id(line));
        }
        for (std::set<int>::iterator x = s.begin(); x != s.end(); x++) {
            auto y = ++x;
            --x;
            if (*y - *x == 2)
                std::cout << *x + 1 << std::endl;
        }
    }
    file.close();
    return 0;
}