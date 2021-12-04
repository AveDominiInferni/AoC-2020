#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<std::pair<int, int>> v;
        std::string line1, line2;
        std::getline(file, line1);
        std::getline(file, line2);
        std::stringstream ss(line2);
        std::string field;
        for (int i = 0; std::getline(ss, field, ','); i++) {
            if (field == "x")
                continue;
            v.push_back({std::stoi(field), i});
        }
        file.close();

        //still more optimization to do
        unsigned long long ts = 0, step = 1;
        for (int i = 0; i < v.size();) {
            if ((ts + v.at(i).second) % v.at(i).first != 0)
                ts += step;
            else {
                step *= v.at(i).first;
                i++;
            }
        }
        std::cout << ts << std::endl;
    }
    return 0;
}