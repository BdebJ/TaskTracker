cmake_minimum_required(VERSION 3.21)

project(TaskTracker)

# Set C++ standard version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files from each module
file(GLOB_RECURSE UTIL_SOURCES "src/Utility/*.cpp" "src/Utility/*.h")
file(GLOB_RECURSE TASK_SOURCES "src/Task/*.cpp" "src/Task/*.h")
file(GLOB_RECURSE TRACKER_SOURCES "src/TaskTracker/*.cpp" "src/TaskTracker/*.h")
file(GLOB_RECURSE UI_SOURCES "src/UserInterface/*.cpp" "src/UserInterface/*.h")

# Combine all sources
set(SOURCES
    ${UTIL_SOURCES}
    ${TASK_SOURCES}
    ${TRACKER_SOURCES}
    ${UI_SOURCES}
    "src/main.cpp"
)

# Add the executable
add_executable(TaskTracker ${SOURCES})