#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include "../Task/Task.h"



namespace utils {
    int readInt();
    std::string readLine();
    std::string strip(const std::string& s);
    void clearConsole();
    void printTaskTable(const std::vector<Task>&);
}