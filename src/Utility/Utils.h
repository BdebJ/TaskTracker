#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include "../Task/Task.h"

namespace utils {
    std::string strip(const std::string& s);
    int readInt();
    std::string readLine();
    void clearConsole();
    void printTaskTable(const std::vector<Task>&);
}