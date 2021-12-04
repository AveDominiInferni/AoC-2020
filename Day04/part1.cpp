#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>

bool passport_valid(const std::unordered_set <std::string> &p) {
    if (p.size() == 8 || (p.size() == 7 && p.find("cid") == p.end()))
        return true;
    return false;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::unordered_set <std::string> passport;
        std::string line;
        unsigned int counter = 0;
        while(std::getline(file, line)) {
            if (line.length() == 0) {
                if (passport_valid(passport))
                    counter++;
                passport.clear();
                continue;
            }
            std::stringstream ss(line);
            std::string field;
            while(std::getline(ss, field, ' '))
                passport.insert(field.substr(0, 3));
        }
        if (passport_valid(passport))
            counter++;
        std::cout << counter << std::endl;
    }
    file.close();
    return 0;
}