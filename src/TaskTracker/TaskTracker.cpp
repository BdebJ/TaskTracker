#include "TaskTracker.h"

std::vector<Task> TaskTracker::getTasks() const {
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

Task* TaskTracker::getTaskDetails(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&title](const Task& task) {
        return task.getTitle() == title;
        });

    if (it != tasks.end()) {
        return &(*it);
    }
    else {
        return nullptr;
    }
}

void TaskTracker::saveTasksToCSV(const std::string& filename) {
    char* homeDir = nullptr;
#ifdef _WIN32
    homeDir = std::getenv("USERPROFILE");
    if (homeDir) {
        fs::path documentsPath = fs::path(homeDir) / "OneDrive" / "Documents" / "Taskfiles";
#else
    homeDir = std::getenv("HOME");
    if (homeDir) {
        fs::path documentsPath = fs::path(homeDir) / "Documents" / "Taskfiles";
#endif

        fs::create_directories(documentsPath);
        fs::path filePath = documentsPath / filename;

        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filePath << std::endl;
            return;
        }

        for (const Task& task : tasks) {
            outFile << task.getTitle() << "|"
                    << task.getDescription() << "|"
                    << task.getStartTime() << "|"
                    << task.getEndTime() << "|"
                    << (task.isCompleted() ? "1" : "0") 
                    << "\n";
        }
        outFile.close();
    }
    else {
        std::cerr << "Error getting home directory." << std::endl;
    }
}

void TaskTracker::loadTasksFromCSV(const std::string& filename) {
    char* homeDir = nullptr;
#ifdef _WIN32
    homeDir = std::getenv("USERPROFILE");
    if (homeDir) {
        fs::path documentsPath = fs::path(homeDir) / "OneDrive" / "Documents" / "Taskfiles";
#else
    homeDir = std::getenv("HOME");
    if (homeDir) {
        fs::path documentsPath = fs::path(homeDir) / "Documents" / "Taskfiles";
#endif 

        fs::path filePath = documentsPath / filename;

        if (!fs::exists(filePath)) {
            std::cerr << "Taskfile not found. Skipping loading." << std::endl;
            return;
        }

        std::ifstream inFile(filePath);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream lineSS(line);
            std::string title, description, startTime, endTime, completedStr;

            if (std::getline(lineSS, title, '|') &&
                std::getline(lineSS, description, '|') &&
                std::getline(lineSS, startTime, '|') &&
                std::getline(lineSS, endTime, '|') &&
                std::getline(lineSS, completedStr)) {
                bool completed = (completedStr == "1");
                tasks.emplace_back(title, description, startTime, endTime, completed);
            }
            else {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
        inFile.close();
    }
    else {
        std::cerr << "Error getting home directory." << std::endl;
    }
}

bool TaskTracker::addTask(const std::string& title, 
                          const std::string& description, 
                          const std::string& startTime,
                          const std::string& endTime, 
                          bool completed) {
    size_t initialSize = tasks.size();
    Task newTask(title, description, startTime, endTime, completed);
    tasks.push_back(newTask);

    return tasks.size() > initialSize;
}

bool TaskTracker::deleteTask(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&title](const Task& task) {
        return task.getTitle() == title;
        });

    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    else {
        return false;
    }
}

bool TaskTracker::completeTask(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&title](Task& task) {
        return task.getTitle() == title;
        });

    if (it != tasks.end()) {
        it->editCompletion(true);
        it->setEndTime(utils::timePointToString(utils::currentTime()));
        return true;
    }
    else {
        return false;
    }
}
