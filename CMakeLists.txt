cmake_minimum_required(VERSION 3.10)

# Project name
project(borgerlang)

# Use C++11, we don't necessarily need anything newer (yet).
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Borgerlang compiler executable
add_executable(borgerlang src/main.cpp)