#include <iostream>
#include <fstream>
#include <utility>

unsigned int count_occurences(const std::string &s, char c) {
    unsigned int counter = 0;
    for (int i = 0; i < s.length(); i++)
        if (s.at(i) == c)
            counter++;
    return counter;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::size_t num_of_valid_passwords = 0;
        while (std::getline(file, line)) {
            std::size_t hypen_pos = line.find('-');
            std::size_t colon_pos = line.find(':');
            std::pair <int, int> interval (
                std::stoi(line.substr(0, hypen_pos)), 
                std::stoi(line.substr(hypen_pos + 1, colon_pos - hypen_pos - 2))
            );
            char letter = line.at(colon_pos - 1);
            std::string password = line.substr(colon_pos + 2);
            std::size_t num_of_occurences = count_occurences(password, letter);
            if (interval.first <= num_of_occurences && num_of_occurences <= interval.second)
                num_of_valid_passwords++;
        }
        std::cout << num_of_valid_passwords << std::endl;
    }
    file.close();
    return 0;
}