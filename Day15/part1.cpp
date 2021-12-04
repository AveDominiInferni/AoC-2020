#include <iostream>
#include <vector>

int main() {
    uint64_t limit = 2020;
    std::vector<uint64_t> v {15,12,0,14,3,1};
    for (int i = v.size() - 2; i >= 0; i--) {
        if (v.at(i) == v.at(v.size() - 1)) {
            v.push_back(v.size() - i - 1);
            if (v.size() >= limit)
                break;
            i = v.size() - 1;
        }
        if (i == 0) {
            v.push_back(0);
            i = v.size() - 1;
        }
        if (v.size() >= limit)
            break;
    }
    std::cout << v.at(v.size() - 1) << std::endl;
    return 0;
}