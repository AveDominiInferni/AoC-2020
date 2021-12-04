#include <iostream>
#include <fstream>
#include <set>

int count_steps(const std::set<int> &s, int step) {
    auto x = s.begin();
    auto y = x;
    y++;
    int k = 0;
    for (x, y ; y != s.end() ; x++, y++)
        if (*y - *x == step)
            k++;
    return k;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::set<int> s;
        s.insert(0);
        while (std::getline(file, line))
            s.insert(std::stoi(line));
        s.insert(*s.rbegin() + 3);
        std::cout << count_steps(s, 1) * count_steps(s, 3) << std::endl;
    }
    file.close();
    return 0;
}