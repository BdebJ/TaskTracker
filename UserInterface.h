#pragma once
#include "TaskTracker.h"

class UserInterface {
private:
    TaskTracker taskTracker;
    bool isRunning = true;
public:
    void run();
    void displayMenu();
    void processChoice(int choice);
    void addTask();
    void listTasks();
    void searchTasks();
    void markComplete();
    void removeTask();
    void viewTaskDetails();
};
