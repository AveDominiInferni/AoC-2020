#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::deque<unsigned long long> d;
        std::vector<unsigned long long> s;
        unsigned long long invalid_number;
        for (int i = 0; i < 25 ; i++) {
            std::getline(file, line);
            s.push_back(std::stoull(line));
            d.push_back(std::stoull(line));
        }
        while (std::getline(file, line)) {
            unsigned long long number = std::stoull(line);
            bool found = false;
            for (int i = 0; i < d.size() - 1; i++) {
                for (int j = i + 1; j < d.size(); j++) {
                    if (d.at(i) + d.at(j) == number) {
                        d.pop_front();
                        d.push_back(number);
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }
            if (!found) {
                invalid_number = number;
                break;
            }
            s.push_back(number);
        }

        unsigned long long result = 0;
        for (auto i = s.begin(); i != s.end() ; i++) {
            unsigned long long sum = 0;
            auto j = i;
            j++;
            for (j; j != s.end(); j++) {
                sum += *j;
                if (sum > invalid_number)
                    break;

                if (sum == invalid_number) {
                    unsigned long long min_num = *i, max_num = *j;
                    j++;
                    auto it = i;
                    do {
                        if (*it < min_num)
                            min_num = *it;
                        else if (*it > max_num)
                            max_num = *it;
                        it++;
                    } while (it != j);
                    result = min_num + max_num;
                    break;
                }
            }
            if (result != 0)
                break;
        }
        std::cout << result << std::endl;
    }
    file.close();
    return 0;
}