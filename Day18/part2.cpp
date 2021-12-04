#include <iostream>
#include <fstream>
#include <deque>

uint64_t calculate(const std::string &s) {
    std::string p(s);
    while (true) {
        auto op = p.find('(');
        if (op != std::string::npos) {
            int op_count = 0;
            for (int i = op + 1; i < p.size(); i++) {
                if (p.at(i) == '(')
                    op_count++;
                else if (p.at(i) == ')') {
                    if (op_count == 0) {
                        p.replace(op, i - op + 1, std::to_string(calculate(p.substr(op + 1, i - op - 1))));
                        break;
                    }
                    else
                        op_count--;
                }
            }   
        }
        else
            break;
    }
    std::deque<uint64_t> n;
    std::deque<char> o;
    for (int i = 0; i < p.size(); i++) {
        if (isdigit(p.at(i))) {
            uint8_t j = 1;
            while (i + j < p.size() && isdigit(p.at(i + j)))
                j++;
            n.push_back(std::stoull(p.substr(i, j)));
            i += j;
        }
        else if (p.at(i) != ' ')
            o.push_back(p.at(i));

    }
    for (int i = 0; i < o.size(); i++) {
        if (o.at(i) == '+') {
            n.at(i) = n.at(i) + n.at(i + 1);
            n.erase(n.begin() + i + 1);
            o.erase(o.begin() + i);
            i--;
        }
    }
    for (int i = 0; i < o.size(); i++) {
        n.at(i) = n.at(i) * n.at(i + 1);
        n.erase(n.begin() + i + 1);
        o.erase(o.begin() + i);
        i--;
    }
    return n.at(0);
}
int main() {
    std::ifstream file("input.txt");
    std::string line;
    uint64_t sum = 0;
    while(std::getline(file, line)) {
        sum += calculate(line);
    }
    std::cout << sum << std::endl;
    return 0;
}