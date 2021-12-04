#include <iostream>
#include <fstream>
#include <utility>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        unsigned int num_of_valid_passwords = 0;
        while (std::getline(file, line)) {
            std::size_t hypen_pos = line.find('-');
            std::size_t colon_pos = line.find(':');
            std::pair <int, int> positions (
                std::stoi(line.substr(0, hypen_pos)), 
                std::stoi(line.substr(hypen_pos + 1, colon_pos - hypen_pos - 2))
            );
            char letter = line.at(colon_pos - 1);
            std::string password = line.substr(colon_pos + 2);
            if ((password.at(positions.first - 1) == letter) != (password.at(positions.second - 1) == letter))
                num_of_valid_passwords++;
        }
        std::cout << num_of_valid_passwords << std::endl;
    }
    file.close();
    return 0;
}