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
        return utils::strip(line);
    }

    std::string strip(const std::string& s) {
        size_t f = s.find_first_not_of(' ');
        size_t l = s.find_last_not_of(' ');

        if (f == std::string::npos || l == std::string::npos) {
            return "";
        }
        return std::string(s.begin() + f, s.begin() + l + 1);
    }

    std::string timePointToString(const ch::system_clock::time_point& timePoint) {
        auto time = ch::system_clock::to_time_t(timePoint);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    ch::system_clock::time_point stringToTimePoint(const std::string& timeStr) {
        std::tm tm_time = {};
        std::istringstream ss(timeStr);
        ss >> std::get_time(&tm_time, "%Y-%m-%d %H:%M:%S");
        return ch::system_clock::from_time_t(std::mktime(&tm_time));
    }

    ch::system_clock::time_point currentTime() {
        return ch::system_clock::now();
    }

    void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void printTaskTable(const std::vector<Task>& tasks) {
        int totalWidth = 120;

        std::cout << std::setw(totalWidth) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

        std::cout << std::setw(20) << std::left << "Title"
                  << std::setw(40) << std::left << "Description"
                  << std::setw(25) << std::left << "Start Time"
                  << std::setw(25) << std::left << "End Time"
                  << std::setw(10) << std::right << "Completed" << std::endl;
        std::cout << std::string(totalWidth, '-') << std::endl;

        for (const Task& task : tasks) {
            std::cout << std::setw(20) << std::left << task.getTitle().substr(0, 20)
                      << std::setw(40) << std::left << task.getDescription().substr(0,35)
                      << std::setw(25) << std::left << task.getStartTime()
                      << std::setw(25) << std::left << (task.getEndTime() == "0" ? "Running Task" : task.getEndTime())
                      << std::setw(10) << std::right << (task.isCompleted() ? "Yes" : "No") << std::endl;
        }
        std::cout << std::string(totalWidth, '=') << std::endl;
    }



}

