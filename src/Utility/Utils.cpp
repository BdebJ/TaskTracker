#include "Utils.h"

namespace utils {
    int readInt() {
        int value;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    std::string readLine() {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }
}