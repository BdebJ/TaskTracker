#include "Task.h"

Task::Task(const std::string& title, 
           const std::string& description, 
           bool completed) 
            : 
           title(title), 
           description(description), 
           completed(completed) {}

const std::string& Task::getTitle() const {
    return title;
}

const std::string& Task::getDescription() const {
    return description;
}

const bool Task::isCompleted() const {
    return completed;
}

void Task::editTitle(const std::string& newTitle) {
    title = newTitle;
}

void Task::editDescription(const std::string& newDescription) {
    description = newDescription;
}

void Task::editCompletion(const bool completionStatus) {
    completed = completionStatus;
}