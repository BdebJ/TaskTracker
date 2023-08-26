#pragma once
#include <string>

class Task {
private:
    std::string title;
    std::string description;
    std::string startTime;
    std::string endTime;
    bool completed;

public:
    Task(const std::string& title, 
         const std::string& description,
         const std::string& startTime, 
         const std::string& endTime, 
         bool completed);

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const bool isCompleted() const;
    const std::string& getStartTime() const;
    const std::string& getEndTime() const;
    void editTitle(const std::string&);
    void editDescription(const std::string&);
    void setStartTime(const std::string&);
    void setEndTime(const std::string&);
    void editCompletion(const bool);
};
