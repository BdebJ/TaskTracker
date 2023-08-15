# CMakeList.txt : CMake project for TaskTracker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project ("TaskTracker")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

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

# Set C++ standard version
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TaskTracker PROPERTY CXX_STANDARD 20)
endif()