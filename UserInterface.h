// UserInterface.h
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "TaskTracker.h"

class UserInterface {
private:
    TaskTracker taskTracker;

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
