#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


class rule {
public:
    std::string name;
    std::pair<uint32_t, uint32_t> range1;
    std::pair<uint32_t, uint32_t> range2;
    std::vector<uint8_t> compatible_fields;

    rule(std::string name, uint32_t n1, uint32_t n2, uint32_t n3, uint32_t n4) {
        rule::name = name;
        range1 = {n1, n2};
        range2 = {n3, n4};
        compatible_fields.resize(0);
    }
    bool in_range(const uint32_t n) const {
    if ((n >= range1.first && n <= range1.second) || (n >= range2.first && n <= range2.second))
        return true;
    return false;
    }
    void remove(const uint8_t n) {
        auto it = std::find(compatible_fields.begin(), compatible_fields.end(), n);
        if (it != compatible_fields.end())
            compatible_fields.erase(it);
    }
};

void parse_rules(std::vector<rule> &rules, const std::string &line) {
    std::string name = line.substr(0, line.find(':'));
    uint32_t fields_i = line.find(':') + 2;
    std::string fields = line.substr(fields_i);
    uint32_t first_space = fields.find(' ');
    std::string field1 = fields.substr(0, first_space);
    std::string field2 = fields.substr(first_space + 4);
    uint32_t first_hyphen = field1.find('-');
    uint32_t second_hyphen = field2.find('-');
    std::vector<uint32_t> temp;
    rules.push_back(rule(name, std::stoul(field1.substr(0, first_hyphen)), std::stoul(field1.substr(first_hyphen + 1)),
        std::stoul(field2.substr(0, second_hyphen)), std::stoul(field2.substr(second_hyphen + 1))));
}

void parse_ticket(const std::vector<rule> &rules, std::vector<std::vector<uint32_t>> &tickets, const std::string &line) {
    std::stringstream ss(line);
    std::string field;
    std::vector<uint32_t> ticket;
    while (std::getline(ss, field, ',')) 
        ticket.push_back(std::stoul(field));
    for (int i = 0; i < ticket.size(); i++) {
        bool passed = false;
        for (int j = 0; j < rules.size(); j++) {
            if (rules.at(j).in_range(ticket.at(i))) {
                passed = true;
                break;
            }
        }
        if (!passed)
            return;
    }
    tickets.push_back(ticket);
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<rule> rules;
    std::vector<std::vector<uint32_t>> tickets;

    while (std::getline(file, line)) {
        if (line.length() == 0)
            break;
        parse_rules(rules, line);
    }

    std::string junk;
    std::getline(file, junk);
    std::getline(file, line);
    parse_ticket(rules, tickets, line);
    std::getline(file, junk);
    std::getline(file, junk);
    while(std::getline(file, line)) 
        parse_ticket(rules, tickets, line);

    for (int j = 0; j < rules.size(); j++) { // looping ticket fields
        for (int k = 0; k < rules.size(); k++) { // looping rules
            bool passed = true;
            for (int i = 0; i < tickets.size(); i++) { // looping tickets
                if (!rules.at(k).in_range(tickets.at(i).at(j))) {
                    passed = false;
                    break;
                }
            }
            if (passed)
                rules.at(k).compatible_fields.push_back(j);
        }
    }

    for (;;) {
        bool solved = true;
        for (int i = 0; i < rules.size(); i++) {
            if (rules.at(i).compatible_fields.size() == 1) {
                auto temp = rules.at(i).compatible_fields.at(0);
                for (int j = 0; j < rules.size(); j++)
                    if (j != i)
                        rules.at(j).remove(temp);
            }
            else
                solved = false;
        }
        if (solved)
            break;
    }
    
    uint64_t result = 1;
    for (int i = 0; i < rules.size(); i++) 
        if (rules.at(i).name.substr(0, 9) == "departure")
            result *= tickets.at(0).at(rules.at(i).compatible_fields.at(0));
    std::cout << result << std::endl;
    
    return 0;
}