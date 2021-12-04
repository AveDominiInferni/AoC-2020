#include <iostream>
#include <fstream>
#include <vector>

class instruction {
public:
    std::string operation;
    int step;
    bool executed;
    instruction(std::string o, int s) { operation = o; step = s; executed = false; }
};

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::vector<instruction> v;
        while(std::getline(file, line)) {
            int step = std::stoi(line.substr(5));
            if (line.at(4) == '-')
                step = -step;
            v.push_back(instruction(line.substr(0, 3), step));
        }
        int i = 0;
        int acc = 0;
        while (v.at(i).executed == false) {
            v.at(i).executed = true;
            if (v.at(i).operation == "jmp") {
                i += v.at(i).step;
                continue;
            }
            else if (v.at(i).operation == "acc")
                acc += v.at(i).step;
            i++;
        }
        std::cout << acc << std::endl;
    }
    file.close();
    return 0;
}