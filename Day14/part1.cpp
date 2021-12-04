#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>

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

uint64_t mask_num (uint64_t broj, std::string m) {
    std::string b = dec_to_bit36(broj);
    for (int i = 0; i < b.length(); i++)
        if (m.at(i) != 'X')
            b.at(i) = m.at(i);
    return bit36_to_dec(b);
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::unordered_map<std::string, uint64_t> m;
        std::string line;
        std::string mask;
        int i = 0;
        while (std::getline(file, line)) {
            i++;
            if (line.substr(0, 4) == "mask")
                mask = line.substr(7);
            else {
                int key_length = line.find(']') - 4;
                std::string mem_key = line.substr(4, key_length);
                m[mem_key] = mask_num(std::stoull(line.substr(key_length + 8)), mask);
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