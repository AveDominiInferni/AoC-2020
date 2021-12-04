#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::unordered_map<char, uint32_t> yes_answers;
        std::string line;
        uint32_t counter = 0;
        uint32_t person_counter = 0;
        while(std::getline(file, line)) {
            if (line.length() == 0) {
                for (auto x : yes_answers)
                    if (x.second == person_counter)
                        counter++;
                person_counter = 0;
                yes_answers.clear();
                continue;
            }
            for (char c : line) {
                if (yes_answers.find(c) == yes_answers.end())
                    yes_answers.insert({c, 1});
                else
                    yes_answers.at(c) += 1;
            }
            person_counter++;
        }
        for (auto x : yes_answers) {
            std::cout << x.first << " : " << x.second << std::endl;
        }
        for (auto x : yes_answers)
            if (x.second == person_counter)
                counter++;
        std::cout << counter << std::endl;
    }
    file.close();
    return 0;
}