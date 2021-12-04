#include <iostream>
#include <fstream>

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
    int max_id = 0;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            int temp_id = get_id(line);
            if (temp_id > max_id)
                max_id = temp_id;
        }
        std::cout << max_id << std::endl;
    }
    file.close();
    return 0;
}