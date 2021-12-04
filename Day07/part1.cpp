#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>

class bag {
public:
    std::string color;
    std::vector<std::string> contained_in;
    bag(const std::string &s) { color = s; }
};

void count(const std::vector<bag> &b, std::unordered_set<std::string> &cache, const std::string &color) {
    for (int i = 0; i < b.size(); i++) {
        if (b.at(i).color == color) {
            for (int j = 0; j < b.at(i).contained_in.size(); j++) {
                cache.insert(b.at(i).contained_in.at(j));
                count(b, cache, b.at(i).contained_in.at(j));
            }
            break;
        }
    }
}

int main() {
    std::ifstream file("input.txt");
    std::vector<bag> bags;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("no other") != std::string::npos)
            continue;
        std::stringstream ss(line);
        std::string field;
        std::getline(ss, field);
        auto pos = field.find("bag");
        std::string bag1 = line.substr(0, pos - 1);
        std::string rest = line.substr(pos + 12);
        std::stringstream ss2(rest);
        while (std::getline(ss2, field, ',')) {
            pos = field.find("bag");
            std::string temp = field.substr(3, pos - 4); 
            bool found = false;   
            for (int i = 0; i < bags.size(); i++) {
                if (bags.at(i).color == temp) {
                    bags.at(i).contained_in.push_back(bag1);
                    found = true;
                    break;
                }
            }
            if (!found) {
                bag bag2(temp);
                bag2.contained_in.push_back(bag1);
                bags.push_back(bag2);
            }
        }
    }

    std::unordered_set<std::string> cache;
    count(bags, cache, "shiny gold");
    std::cout << cache.size();
    return 0;
}