#include <iostream>
#include <fstream>
#include <deque>
#include <unordered_map>
#include <algorithm>

unsigned long long count_paths(const std::deque<int> &d, std::unordered_map<int, unsigned long long> &cache, int i = 0) {
    unsigned long long total = 0;
    if (i == d.size() - 1)
        return 1;
    if (cache.find(i) != cache.end())
        return cache.at(i);
    if (i + 1 < d.size())
        total += count_paths(d, cache, i + 1);
    if (i + 2 < d.size() && d.at(i + 2) - d.at(i) <= 3)
        total += count_paths(d, cache, i + 2);
    if (i + 3 < d.size() && d.at(i + 3) - d.at(i) <= 3)
        total += count_paths(d, cache, i + 3);
    cache.insert({i, total});
    return total;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::deque<int> d;
        std::unordered_map<int, unsigned long long> cache;
        d.push_front(0);
        while (std::getline(file, line))
            d.push_back(std::stoi(line));
        std::sort(d.begin(), d.end());
        d.push_back(d.at(d.size() - 1) + 3);
        std::cout << count_paths(d, cache);
    }
    file.close();
    return 0;
}