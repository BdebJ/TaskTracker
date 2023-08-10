#pragma once
#include <vector>
#include "Task.h"

class TaskTracker {
private:
    std::vector<Task> tasks;

public:
    std::vector<Task> listTasks() const;
    std::vector<Task> searchTasks(const std::string&) const;

    Task getTaskDetails(const std::string&);
    void addTask(const std::string&, const std::string&, bool);
    void deleteTask(const std::string&);
    void completeTask(const std::string&);
};
