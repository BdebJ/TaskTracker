#include "UserInterface.h"

void UserInterface::run() {
    int choice;
    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        processChoice(choice);
    }
}

void UserInterface::displayMenu() {
    std::cout << "===== Task Tracker Menu =====" << std::endl;
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. List Tasks" << std::endl;
    std::cout << "3. Search Tasks" << std::endl;
    std::cout << "4. Complete Task" << std::endl;
    std::cout << "5. Delete Task" << std::endl;
    std::cout << "6. View Task Details" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

void UserInterface::processChoice(int choice) {
    switch (choice) {
    case 1:
        addTask();
        break;
    case 2:
        listTasks();
        break;
    case 3:
        searchTasks();
        break;
    case 4:
        markComplete();
        break;
    case 5:
        removeTask();
        break;
    case 6:
        viewTaskDetails();
        break;
    case 7:
        std::cout << "Exiting the application." << std::endl;
        exit(0);
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void UserInterface::addTask() {
    std::string title, description;
    std::string completedInput;

    std::cout << "Enter task title: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    std::cout << "Enter task description: ";
    std::cin.ignore();
    std::getline(std::cin, description);

    std::cout << "Is the task completed? (Y/N): ";
    std::cin >> completedInput;
    bool completed = (completedInput == "Y" || completedInput == "y");

    taskTracker.addTask(title, description, completed);
    std::cout << "Task added successfully." << std::endl;
}


void UserInterface::listTasks() {
    std::vector<Task> tasks = taskTracker.listTasks();
    if (tasks.empty()) {
        std::cout << "No tasks found." << std::endl;
        return;
    }

    std::cout << "===== Tasks List =====" << std::endl;
    for (const Task& task : tasks) {
        std::cout << "Title: " << task.getTitle() << std::endl;
        std::cout << "Description: " << task.getDescription() << std::endl;
        std::cout << "Completed: " << (task.isCompleted() ? "Yes" : "No") << std::endl;
        std::cout << "=========================" << std::endl;
    }
}

void UserInterface::searchTasks() {
    std::string keyword;

    std::cout << "Enter keyword to search: ";
    std::cin.ignore();
    std::getline(std::cin, keyword);

    std::vector<Task> matchingTasks = taskTracker.searchTasks(keyword);
    if (matchingTasks.empty()) {
        std::cout << "No matching tasks found." << std::endl;
        return;
    }

    std::cout << "===== Matching Tasks =====" << std::endl;
    for (const Task& task : matchingTasks) {
        std::cout << "Title: " << task.getTitle() << std::endl;
        std::cout << "Description: " << task.getDescription() << std::endl;
        std::cout << "Completed: " << (task.isCompleted() ? "Yes" : "No") << std::endl;
        std::cout << "=========================" << std::endl;
    }
}

void UserInterface::markComplete() {
    std::string title;

    std::cout << "Task title of the task to mark as complete: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    taskTracker.completeTask(title);
    //std::cout << "Task marked complete." << std::endl;
}

void UserInterface::removeTask() {
    std::string title;

    std::cout << "Enter the title of the task to remove: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    taskTracker.deleteTask(title);
    //std::cout << "Task removed." << std::endl;
}

void UserInterface::viewTaskDetails() {
    std::string title;

    std::cout << "Enter the title of the task to view details: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    Task task = taskTracker.getTaskDetails(title);
    if (task.getTitle() == "") {
        std::cout << "Task not found." << std::endl;
    }
    else {
        std::cout << "===== Task Details =====" << std::endl;
        std::cout << "Title: " << task.getTitle() << std::endl;
        std::cout << "Description: " << task.getDescription() << std::endl;
        std::cout << "Completed: " << (task.isCompleted() ? "Yes" : "No") << std::endl;
        std::cout << "=========================" << std::endl;
    }
}