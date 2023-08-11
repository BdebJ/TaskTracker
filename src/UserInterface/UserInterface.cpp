#include "UserInterface.h"

void UserInterface::run() {
    int selection;
    taskTracker.loadTasksFromCSV();

    while (isRunning) {
        displayMenu();
        std::cout << "Enter your choice: ";
        selection = utils::readInt();
        processChoice(selection);
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

void UserInterface::processChoice(int selection) {
    switch (selection) {
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
        taskTracker.saveTasksToCSV();
        isRunning = false;
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void UserInterface::addTask() {
    std::string title, description, completedInput;

    std::cout << "Enter task title: ";
    title = utils::readLine();

    std::cout << "Enter task description: ";
    description = utils::readLine();

    bool completed;
    while (true) {
        std::cout << "Is the task completed? (Y/N): ";
        completedInput = utils::readLine();

        if (completedInput == "Y" || completedInput == "y") {
            completed = true;
            break;
        }
        else if (completedInput == "N" || completedInput == "n") {
            completed = false;
            break;
        }
        else {
            std::cout << "Invalid input for task completion status. Please enter 'y' or 'n'." << std::endl;
        }
    }

    taskTracker.addTask(title, description, completed);
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
    keyword = utils::readLine();

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
    title = utils::readLine();

    if (taskTracker.completeTask(title)) {
        std::cout << "Task marked complete." << std::endl;
    }
    else {
        std::cout << "Task not found." << std::endl;
    }
}

void UserInterface::removeTask() {
    std::string title;

    std::cout << "Enter the title of the task to remove: ";
    title = utils::readLine();

    if (taskTracker.deleteTask(title)) {
        std::cout << "Task removed." << std::endl;
    }
    else {
        std::cout << "Task not found." << std::endl;
    }
}

void UserInterface::viewTaskDetails() {
    std::string title;

    std::cout << "Enter the title of the task to view details: ";
    title = utils::readLine();

    Task* taskPtr = taskTracker.getTaskDetails(title);
    if (taskPtr) {
        Task task = *taskPtr;
        std::cout << "===== Task Details =====" << std::endl;
        std::cout << "Title: " << task.getTitle() << std::endl;
        std::cout << "Description: " << task.getDescription() << std::endl;
        std::cout << "Completed: " << (task.isCompleted() ? "Yes" : "No") << std::endl;
        std::cout << "=========================" << std::endl;
    }
    else {
        std::cout << "Task not found." << std::endl;
    }
}