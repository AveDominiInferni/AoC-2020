#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
//135
bool is_string_a_number(const std::string &s) {
    for (int i = 0; i < s.length(); i++)
        if (!isdigit(s.at(i)))
            return false;
    return true;
}

bool is_string_a_color(const std::string &s) {
    if (s.at(0) != '#' || s.length() != 7)
        return false;
    for (int i = 1; i < s.length(); i++)
        if (!(isdigit(s.at(i)) || (s.at(i) >= 'a' && s.at(i) <= 'f')))
            return false;
    return true;
}

bool is_passport_valid(const std::unordered_map <std::string, std::string> &p) {
    if (p.size() != 8 && !(p.size() == 7 && p.find("cid") == p.end()))
        return false;
    if (is_string_a_number(p.at("byr")) && (std::stoi(p.at("byr")) < 1920 || std::stoi(p.at("byr")) > 2002))
        return false;
    if (is_string_a_number(p.at("iyr")) && (std::stoi(p.at("iyr")) < 2010 || std::stoi(p.at("iyr")) > 2020))
        return false;
    if (is_string_a_number(p.at("eyr")) && (std::stoi(p.at("eyr")) < 2020 || std::stoi(p.at("eyr")) > 2030))
        return false;
    std::string value = p.at("hgt");
    int length = 0;
    if (is_string_a_number(value.substr(0, value.length() - 2)))
        length = std::stoi(value.substr(0, value.length() - 2));
    std::string length_unit = value.substr(value.length() - 2);
    if (!((length_unit == "cm" && length >= 150 && length <= 193) || (length_unit == "in" && length >= 59 && length <= 76)))
       return false;
    if (!is_string_a_color(p.at("hcl")))
       return false;
    if (p.at("ecl") != "amb" && p.at("ecl") != "blu" && p.at("ecl") != "brn" && p.at("ecl") != "gry"
        && p.at("ecl") != "grn" && p.at("ecl") != "hzl" && p.at("ecl") != "oth")
        return false;
    if (!is_string_a_number(p.at("pid")) || p.at("pid").length() != 9) 
        return false;
    std::cout << p.at("iyr") << std::endl;
    return true;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::unordered_map <std::string, std::string> passport;
        std::string line;
        unsigned int counter = 0;
        while(std::getline(file, line)) {
            if (line.length() == 0) {
                if (is_passport_valid(passport))
                    counter++;
                passport.clear();
                continue;
            }
            std::stringstream ss(line);
            std::string field;
            while(std::getline(ss, field, ' '))
                passport.insert({field.substr(0, 3), field.substr(4)});
        }
        if (is_passport_valid(passport))
            counter++;
        std::cout << counter << std::endl;
    }
    file.close();
    return 0;
}