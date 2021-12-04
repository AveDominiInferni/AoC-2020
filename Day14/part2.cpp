#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>

typedef std::unordered_map <uint64_t, uint64_t> memory;

std::string dec_to_bit36(uint64_t broj) {
    std::string b = "000000000000000000000000000000000000";
        for (int i = 35; broj != 0; i--) {
            if (broj % 2 != 0)
                b.at(i) = '1';
            broj /= 2;
        }
    return b;
}

uint64_t bit36_to_dec(std::string broj) {
    uint64_t d = 0;
    for (int i = 0; i < broj.length(); i++)
        if (broj.at(broj.length() -  i -  1) == '1')
            d += std::pow(2, i);
    return d;
}

std::string mask_num (uint64_t broj, std::string m) {
    std::string b = dec_to_bit36(broj);
    for (int i = 0; i < b.length(); i++)
        if (m.at(i) != '0')
            b.at(i) = m.at(i);
    return b;
}

void floating_values(memory &m, const std::string &mem_key, const uint64_t dec_num) { 
    int index = mem_key.find('X');
    if (index == std::string::npos) {
        m[bit36_to_dec(mem_key)] = dec_num;
        return;
    }
    else {
        std::string temp_s1 = mem_key;
        temp_s1.at(index) = '0';
        floating_values(m, temp_s1, dec_num);
        std::string temp_s2 = mem_key;
        temp_s2.at(index) = '1';
        floating_values(m, temp_s2, dec_num);
    }
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        memory m;
        std::string line;
        std::string mask;
        while (std::getline(file, line)) {
            if (line.substr(0, 4) == "mask")
                mask = line.substr(7);
            else {
                int key_length = line.find(']') - 4;
                uint64_t mem_key = std::stoull(line.substr(4, key_length));
                uint64_t dec_num = std::stoull(line.substr(key_length + 8));
                std::string bin_num = dec_to_bit36(dec_num);
                floating_values(m, mask_num(mem_key, mask), dec_num);
            }
        }
        uint64_t sum = 0;
        for (auto x : m)
            sum += x.second;
        std::cout << sum << std::endl;
    }
    file.close();
    return 0;
}