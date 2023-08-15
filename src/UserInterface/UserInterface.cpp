#include "UserInterface.h"

void UserInterface::run() {
    int selection;
    std::cout << "Loading tasks from TaskFile" << std::endl;
    taskTracker.loadTasksFromCSV();
    std::cout << taskTracker.getTasks().size() << " tasks found" << std::endl;

    while (isRunning) {
        displayMenu();
        std::cout << "Enter your choice: ";
        selection = utils::readInt();
        processChoice(selection);
    }
}

void UserInterface::displayMenu() {
    std::cout << "===== Task Tracker Menu =====" << "\n";
    std::cout << "1. Add Task" << "\n";
    if (!taskTracker.getTasks().empty()) {
        std::cout << "2. List Tasks" << "\n";
        std::cout << "3. Search Tasks" << "\n";
        std::cout << "4. Complete Task" << "\n";
        std::cout << "5. Delete Task" << "\n";
        std::cout << "6. View Task Details" << "\n";
    }
    std::cout << "7. Exit" << "\n";
}

void UserInterface::processChoice(int selection) {
    switch (selection) {
    case 1:
        addTask();
        break;
    case 7:
        std::cout << "Exiting the application." << "\n";
        isRunning = false;
        break;
    default:
        if (!taskTracker.getTasks().empty()) {
            switch (selection) {
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
            default:
                utils::clearConsole();
                std::cout << "Invalid choice. Please try again." << "\n";
            }
        }
    }
}

void UserInterface::addTask() {
    utils::clearConsole();

    std::string title, description, completedInput;
    std::cout << "Enter task title: ";
    title = utils::readLine();

    if (taskTracker.getTaskDetails(title) != nullptr) {
        std::cout << "A task with the same title already exists. Enter a unique title or rename conflicting task title." << "\n";
        std::cout << "Press Enter to continue" << "\n";
        std::cin.get();
        return;
    }

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
            std::cout << "Invalid input for task completion status. Please enter 'y' or 'n'." << "\n";
        }
    }

    if (taskTracker.addTask(title, description, completed)) {
        utils::clearConsole();
        std::cout << "Task added successfully." << "\n";
        taskTracker.saveTasksToCSV();
    }
}


void UserInterface::listTasks() {
    utils::clearConsole();
    std::vector<Task> tasks = taskTracker.getTasks();
    if (tasks.empty()) {
        std::cout << "No tasks found." << "\n";
        return;
    }

    utils::printTaskTable(tasks);
    std::cout << "Press Enter to continue" << "\n";
    std::cin.get();
    utils::clearConsole();
}

void UserInterface::searchTasks() {
    std::string keyword;
    std::cout << "Enter keyword to search: ";
    keyword = utils::readLine();

    utils::clearConsole();
    std::vector<Task> matchingTasks = taskTracker.searchTasks(keyword);
    if (matchingTasks.empty()) {
        std::cout << "No matching tasks found." << "\n";
        return;
    }
    std::cout << "Found " << matchingTasks.size() << " matches." << std::endl;
    utils::printTaskTable(matchingTasks);
    std::cout << "Press Enter to continue" << "\n";
    std::cin.get();
    utils::clearConsole();
}

void UserInterface::markComplete() {
    std::string title;

    std::cout << "Task title of the task to mark as complete: ";
    title = utils::readLine();

    if (taskTracker.completeTask(title)) {
        std::cout << "Task marked complete." << "\n";
        taskTracker.saveTasksToCSV();
    }
    else {
        std::cout << "Task not found." << "\n";
    }
}

void UserInterface::removeTask() {
    std::string title;

    std::cout << "Enter the title of the task to remove: ";
    title = utils::readLine();
    utils::clearConsole();
    if (taskTracker.deleteTask(title)) {
        std::cout << "Task removed." << "\n";
        taskTracker.saveTasksToCSV();
    }
    else {
        std::cout << "Task not found." << "\n";
    }
}

void UserInterface::viewTaskDetails() {
    std::string title;

    std::cout << "Enter the title of the task to view details: ";
    title = utils::readLine();
    utils::clearConsole();
    Task* taskPtr = taskTracker.getTaskDetails(title);
    if (taskPtr) {
        Task task = *taskPtr;
        std::cout << "===== Task Details =====" << "\n";
        std::cout << "Title: " << task.getTitle() << "\n\n";
        std::cout << "Description: " << task.getDescription() << "\n\n";;
        std::cout << "Completed: " << (task.isCompleted() ? "Yes" : "No") << "\n\n";;
        std::cout << "=========================" << "\n";
        std::cout << "Press Enter to continue" << "\n";
        std::cin.get();
        utils::clearConsole();
    }
    else {
        std::cout << "Task not found." << "\n";
    }
}