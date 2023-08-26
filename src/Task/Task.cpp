#include "Task.h"

Task::Task(const std::string& title, 
           const std::string& description,
           const std::string& startTime,
           const std::string& endTime,
           bool completed) 
            : 
           title(title), 
           description(description),
           startTime(startTime),
           endTime(endTime),
           completed(completed) {}

const std::string& Task::getTitle() const {
    return title;
}

const std::string& Task::getDescription() const {
    return description;
}

const std::string& Task::getStartTime() const {
    return startTime;
}

const std::string& Task::getEndTime() const {
    return endTime;
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

void Task::setStartTime(const std::string& startTimeStr) {
    startTime = startTimeStr;
}

void Task::setEndTime(const std::string& endTimeStr) {
    endTime = endTimeStr;
}

void Task::editCompletion(const bool completionStatus) {
    completed = completionStatus;
}