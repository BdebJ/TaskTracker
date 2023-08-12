#include "Utils.h"

namespace utils {
    int readInt() {
        int value;
        std::cin >> value;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    std::string readLine() {
        std::string line;
        std::getline(std::cin, line);
        line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");
        return line;
    }

    void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
}