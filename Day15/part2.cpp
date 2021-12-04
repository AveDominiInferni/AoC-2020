#include <iostream>
#include <map>
#include <deque>
#include <fstream>
// works but too slow and uses too much memory
int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        uint32_t last;
        uint32_t limit = 30000000;
        uint32_t i = 0;
        std::map<uint32_t, std::deque<uint32_t>> m;
        while(std::getline(file, line, ',')) {
            last = std::stoull(line);
            m[last] = {i++};
        }
        m.erase(last);
        i--;

        while (i < limit - 1) {
            auto it = m.find(last);
            if (it == m.end()) {
                m[last].push_back(i++);
                last = 0;
            }
            else {
                uint32_t dist = i - it->second.at(it->second.size() - 1);
                m[last].push_back(i++);
                last = dist;
                if (it->second.size() > 2)
                    it->second.pop_front();               
            }
        }
        /* 
       for (auto x : m) {
            std::cout << x.first << " : { ";
            for (auto y : x.second)
                std::cout << y << " ";
            std::cout << "}" << std::endl;
        }
        */
        std::cout << last << std::endl;
    }
    return 0;
}