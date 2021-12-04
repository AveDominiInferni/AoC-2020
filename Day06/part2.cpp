int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::unordered_map <std::string, std::string> passport;
        std::string line;
        unsigned int counter = 0;
        while(std::getline(file, line)) {
            if (line.length() == 0) {
                if (is_passport_valid(passport))
                    counter++;
                passport.clear();
                continue;
            }
            std::stringstream ss(line);
            std::string field;
            while(std::getline(ss, field, ' '))
                passport.insert({field.substr(0, 3), field.substr(4)});
        }
        if (is_passport_valid(passport))
            counter++;
        std::cout << counter << std::endl;
    }
    file.close();
    return 0;
}