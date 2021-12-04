#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>

class bag {
public:
    std::string color;
    std::vector<std::pair<uint32_t, std::string>> contains;
    bag(const std::string &s) { color = s; }
};

uint64_t count(const std::vector<bag> &b, const std::string &s) {
    uint64_t result = 1;
    for (int i = 0; i < b.size(); i++)
        if (b.at(i).color == s)
            for (int j = 0; j < b.at(i).contains.size(); j++)
                result += count(b, b.at(i).contains.at(j).second) * b.at(i).contains.at(j).first;
    return result;
}

int main() {
    std::ifstream file("input.txt");
    std::vector<bag> bags;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::getline(ss, field);
        auto pos = field.find("bag");
        bag bag1(line.substr(0, pos - 1));
        if (line.find("no other") != std::string::npos) {
            bags.push_back(bag1);
            continue;
        }
        std::string rest = line.substr(pos + 12);
        std::stringstream ss2(rest);
        while (std::getline(ss2, field, ',')) {
            pos = field.find("bag");
            std::string temp = field.substr(1, pos - 2);
            pos = temp.find(" ");
            bag1.contains.push_back({std::stoul(temp.substr(0, pos)), temp.substr(pos + 1)});
        }
        bags.push_back(bag1);
    }
    std::cout << count(bags, "shiny gold") - 1;
    return 0;
}