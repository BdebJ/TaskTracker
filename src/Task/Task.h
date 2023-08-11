#pragma once
#include <string>

class Task {
private:
    std::string title;
    std::string description;
    bool completed;

public:
    Task(const std::string&, const std::string&, bool);

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const bool isCompleted() const;
    void editTitle(const std::string&);
    void editDescription(const std::string&);
    void editCompletion(const bool);
};
