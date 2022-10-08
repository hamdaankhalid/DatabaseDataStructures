cmake_minimum_required(VERSION 3.21)

set(CMAKE_GENERATOR "Ninja")

project(DatabaseDataStructures)

enable_testing()

add_subdirectory(googletest)

add_subdirectory(src)
add_subdirectory(tests)
