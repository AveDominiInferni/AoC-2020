#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::vector<std::vector<char>> layout;
        while (std::getline(file, line)) {
            if (layout.size() == 0) {
                std::vector<char> temp (line.length() + 2, '.');
                layout.push_back(temp);
            }
            std::vector<char> row;
            row.push_back('.');
            for (char x : line)
                row.push_back(x);
            row.push_back('.');
            layout.push_back(row);
        }
        std::vector<char> temp (line.length() + 2, '.');
        layout.push_back(temp);
        std::vector<std::pair<int, int>> queued_changes;
        do {
            queued_changes.clear();
            for (int i = 1 ; i < layout.size() - 1; i++) {
                for (int j = 1 ; j < layout.at(i).size() - 1; j++) {
                    if (layout.at(i).at(j) == 'L') {
                        if (layout.at(i - 1).at(j - 1) != '#' && layout.at(i - 1).at(j) != '#' && layout.at(i - 1).at(j + 1) != '#'
                            && layout.at(i).at(j + 1) != '#' && layout.at(i + 1).at(j + 1) != '#' && layout.at(i + 1).at(j) != '#'
                            && layout.at(i + 1).at(j - 1) != '#' && layout.at(i).at(j - 1) != '#')
                                queued_changes.push_back({i, j});
                    }
                    else if (layout.at(i).at(j) == '#') {
                        int k = 0;
                        if (layout.at(i - 1).at(j - 1) == '#')
                            k++;
                        if (layout.at(i - 1).at(j) == '#')
                            k++;
                        if (layout.at(i - 1).at(j + 1) == '#')
                            k++;
                        if (layout.at(i).at(j + 1) == '#' )
                            k++;
                        if (layout.at(i + 1).at(j + 1) == '#' )
                            k++;
                        if (layout.at(i + 1).at(j) == '#')
                            k++;
                        if (layout.at(i + 1).at(j - 1) == '#' )
                            k++;
                        if (layout.at(i).at(j - 1) == '#')
                            k++;
                        if (k >= 4)
                            queued_changes.push_back({i, j});
                    }
                }
            }  
            for (auto change : queued_changes) {
                if (layout.at(change.first).at(change.second) == 'L')
                    layout.at(change.first).at(change.second) = '#';
                else
                    layout.at(change.first).at(change.second) = 'L';
            }  
        } while(queued_changes.size() != 0);

        int occupied_seats = 0;
        for (int i = 1 ; i < layout.size() - 1; i++)
            for (int j = 1 ; j < layout.at(i).size() - 1; j++)
                if (layout.at(i).at(j) == '#')
                    occupied_seats++;
        std::cout << occupied_seats << std::endl;
    }
    file.close();
    return 0;
}