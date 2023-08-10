#include "TaskTracker.h"

static bool hasMatchingTitle(const Task& task, const std::string& targetTitle) {
    return task.getTitle() == targetTitle;
}

std::vector<Task> TaskTracker::listTasks() const {
    return tasks;
}

std::vector<Task> TaskTracker::searchTasks(const std::string& keyword) const {
    std::vector<Task> matchingTasks;

    for (const Task& task : tasks) {
        if (task.getTitle().find(keyword) != std::string::npos ||
            task.getDescription().find(keyword) != std::string::npos) {
            matchingTasks.push_back(task);
        }
    }
    return matchingTasks;
}

Task TaskTracker::getTaskDetails(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&title](const Task& task) {
        return hasMatchingTitle(task, title);
        });

    if (it != tasks.end()) {
        return *it;  
    }
    else {
        // Handle case when task with the provided title is not found
    }
}

void TaskTracker::addTask(const std::string& title, const std::string& description, bool completed) {
    Task newTask(title, description, completed);
    tasks.push_back(newTask);
}

void TaskTracker::deleteTask(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&title](const Task& task) {
        return hasMatchingTitle(task, title);
        });

    if (it != tasks.end()) {
        tasks.erase(it);
    }
    else {
        // Handle case when task with the provided title is not found
    }
}

void TaskTracker::completeTask(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&title](Task& task) {
        return hasMatchingTitle(task, title);
        });

    if (it != tasks.end()) {
        it->editCompletion(true);
    }
    else {
        // Handle case when task with the provided title is not found
    }
}
