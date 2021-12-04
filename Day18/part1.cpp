#include <iostream>
#include <fstream>

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
    
    uint64_t result = 0;
    char operation = '+';
    for (int i = 0; i < p.size(); i++) {
        if (p.at(i) == '+')
            operation = '+';
        else if (p.at(i) == '*')
            operation = '*';
        else if (isdigit(p.at(i))) {
            int j = 1;
            while (i + j < p.size() && isdigit(p.at(i + j)))
                j++;
            if (operation == '+')
                result += std::stoull(p.substr(i, j));
            else 
                result *= std::stoull(p.substr(i, j));
            i += j;
        }
    }
    return result;
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