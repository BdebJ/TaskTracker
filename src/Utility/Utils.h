#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include <chrono>
#include "../Task/Task.h"

namespace ch = std::chrono;

namespace utils {
    int readInt();
    std::string readLine();
    std::string strip(const std::string& s);
    std::string timePointToString(const ch::system_clock::time_point&);
    ch::system_clock::time_point stringToTimePoint(const std::string&);
    ch::system_clock::time_point currentTime();
    void clearConsole();
    void printTaskTable(const std::vector<Task>&);
}