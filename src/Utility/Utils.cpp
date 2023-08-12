#include "Utils.h"

namespace utils {
    std::string strip(const std::string& s) {
        size_t f = s.find_first_not_of(' ');
        size_t l = s.find_last_not_of(' ');

        if (f == std::string::npos || l == std::string::npos) {
            return "";
        }
        return std::string(s.begin() + f, s.begin() + l + 1);
    }

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
        return utils::strip(line);
    }

    void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void printTaskTable(const std::vector<Task>& tasks) {
        int totalWidth = 120; // Total width of the table

        std::cout << std::setw(totalWidth) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

        std::cout << std::setw(30) << std::left << "Title"
            << std::setw(60) << std::left << "Description"
            << std::setw(20) << std::right << "Completed" << std::endl;
        std::cout << std::string(totalWidth, '-') << std::endl;

        for (const Task& task : tasks) {
            std::cout << std::setw(30) << std::left << task.getTitle().substr(0, 30)
                << std::setw(60) << std::left << task.getDescription().substr(0, 60)
                << std::setw(20) << std::right << (task.isCompleted() ? "Yes" : "No") << std::endl;
        }
        std::cout << std::string(totalWidth, '=') << std::endl;
    }
}

