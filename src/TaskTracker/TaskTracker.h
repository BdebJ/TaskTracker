#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "../Utility/Utils.h"
#include "../Task/Task.h"

namespace fs = std::filesystem;

class TaskTracker {
private:
    std::vector<Task> tasks;

public:
    std::vector<Task> getTasks() const;
    std::vector<Task> searchTasks(const std::string&) const;

    Task* getTaskDetails(const std::string&);
    void saveTasksToCSV(const std::string & = "TaskList.csv");
    void loadTasksFromCSV(const std::string& = "TaskList.csv");
    bool addTask(const std::string&, const std::string&, bool);
    bool deleteTask(const std::string&);
    bool completeTask(const std::string&);
};
