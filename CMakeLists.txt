cmake_minimum_required(VERSION 3.15)
project(git-time)
add_subdirectory(src)

# Finds if git is present on the system
find_package(Git REQUIRED)
if(NOT GIT_FOUND)
  message(FATAL_ERROR "git not found")
endif()

# Checks for libgit2
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
find_package(libgit2 REQUIRED)

enable_testing()
include(CTest)
add_subdirectory(test)
