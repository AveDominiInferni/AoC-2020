#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool is_field_valid(const std::vector<std::vector<uint32_t>> &rules, const uint32_t field) {
    for (int i = 0; i < rules.size(); i++)
        if ((field >= rules.at(i).at(0) && field <= rules.at(i).at(1)) || (field >= rules.at(i).at(2) && field <= rules.at(i).at(3)))
            return true;
    return false;
}

void parse_input(std::vector<std::vector<uint32_t>> &rules, const std::string &line) {
    uint32_t fields_i = line.find(':') + 2;
    std::string fields = line.substr(fields_i);
    uint32_t first_space = fields.find(' ');
    std::string field1 = fields.substr(0, first_space);
    std::string field2 = fields.substr(first_space + 4);
    uint32_t first_hyphen = field1.find('-');
    uint32_t second_hyphen = field2.find('-');
    std::vector<uint32_t> temp;
    temp.push_back(std::stoul(field1.substr(0, first_hyphen)));
    temp.push_back(std::stoul(field1.substr(first_hyphen + 1)));
    temp.push_back(std::stoul(field2.substr(0, second_hyphen)));
    temp.push_back(std::stoul(field2.substr(second_hyphen + 1)));
    rules.push_back(temp);
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::vector<uint32_t>> rules;
    while (std::getline(file, line)) {
        if (line.length() == 0)
            break;
        parse_input(rules, line);
    }

    std::string junk;
    for (int i = 0; i < 4; i++)
        std::getline(file, junk);
    std::vector<std::vector<uint32_t>> tickets;
    uint64_t invalid_values = 0;

    while( std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<uint32_t> ticket;
        while (std::getline(ss, field, ','))
            ticket.push_back(std::stoul(field));
        tickets.push_back(ticket);
    }

    for (int i = 0; i < tickets.size(); i++) 
        for (int j = 0; j < tickets.at(0).size(); j++)
            if (!is_field_valid(rules, tickets.at(i).at(j)))
                invalid_values += tickets.at(i).at(j);

    std::cout << invalid_values << std::endl;
    return 0;
}