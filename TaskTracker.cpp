#include "TaskTracker.h"

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
        return task.getTitle() == title;
        });

    if (it != tasks.end()) {
        return *it;  
    }
    else {
        // Handle case when task with the provided title is not found
    }
}

void TaskTracker::saveTasksToCSV(const std::string& filename) {
    char* homeDir = nullptr;
    size_t len;
    errno_t err = _dupenv_s(&homeDir, &len, "HOME");

    if (err != 0 || homeDir == nullptr) {
        err = _dupenv_s(&homeDir, &len, "USERPROFILE");
    }

    std::string filePath;  // Define filePath here

    if (err == 0 && homeDir) {
        #ifdef _WIN32
            filePath = std::string(homeDir) + "\\Documents\\Tasks\\" + filename;
        #else
            filePath = std::string(homeDir) + "/Documents/Tasks/" + filename;
        #endif

        fs::create_directory(fs::path(filePath).parent_path());
        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filePath << std::endl;
            free(homeDir);
            return;
        }

        for (const Task& task : tasks) {
            outFile << task.getTitle() << "," << task.getDescription() << "," << (task.isCompleted() ? "1" : "0") << "\n";
        }
        outFile.close();
        free(homeDir);
    }
    else {
        std::cerr << "Error getting home directory." << std::endl;
    }

    if (!filePath.empty() && !fs::exists(filePath)) {
        std::cerr << "Couldnt create Taskfile" << std::endl;
    }
}

void TaskTracker::loadTasksFromCSV(const std::string& filename) {
    char* homeDir = nullptr;
    size_t len;
    errno_t err = _dupenv_s(&homeDir, &len, "HOME");

    if (err != 0 || homeDir == nullptr) {
        err = _dupenv_s(&homeDir, &len, "USERPROFILE");
    }

    if (err == 0 && homeDir) {
        std::string filePath;

        #ifdef _WIN32
            filePath = std::string(homeDir) + "\\Documents\\Tasks\\" + filename;
        #else
            filePath = std::string(homeDir) + "/Documents/Tasks/" + filename;
        #endif

        if (!fs::exists(filePath)) {
            std::cerr << "Taskfile not found. Skipping loading." << std::endl;
            free(homeDir);
            return;
        }

        std::ifstream inFile(filePath);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filePath << std::endl;
            free(homeDir);
            return;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream lineSS(line);
            std::string title, description, completedStr;

            if (std::getline(lineSS, title, ',') &&
                std::getline(lineSS, description, ',') &&
                std::getline(lineSS, completedStr)) {
                bool completed = (completedStr == "1");
                tasks.emplace_back(title, description, completed);
            }
            else {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
        inFile.close();
        free(homeDir);
    }
    else {
        std::cerr << "Error getting home directory." << std::endl;
    }
}


void TaskTracker::addTask(const std::string& title, const std::string& description, bool completed) {
    Task newTask(title, description, completed);
    tasks.push_back(newTask);
}

void TaskTracker::deleteTask(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&title](const Task& task) {
        return task.getTitle() == title;
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
        return task.getTitle() == title;
        });

    if (it != tasks.end()) {
        it->editCompletion(true);
    }
    else {
        // Handle case when task with the provided title is not found
    }
}
