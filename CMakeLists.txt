cmake_minimum_required(VERSION 3.21)

project(DatabaseDataStructures)

enable_testing()

# git submodule
add_subdirectory(googletest)

add_subdirectory(src)
add_subdirectory(tests)
