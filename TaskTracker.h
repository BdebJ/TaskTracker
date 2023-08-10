#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cctype>
#include <cstdlib>
#include "Task.h"

namespace fs = std::filesystem;

class TaskTracker {
private:
    std::vector<Task> tasks;

public:
    std::vector<Task> listTasks() const;
    std::vector<Task> searchTasks(const std::string&) const;

    Task getTaskDetails(const std::string&);
    void saveTasksToCSV(const std::string & = "TaskList.csv");
    void loadTasksFromCSV(const std::string& = "TaskList.csv");
    void addTask(const std::string&, const std::string&, bool);
    void deleteTask(const std::string&);
    void completeTask(const std::string&);

};
