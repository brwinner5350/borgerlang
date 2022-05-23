cmake_minimum_required(VERSION 3.10)

# Project name
project(borgerlang)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Includes & definitions
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Borgerlang compiler executable
add_executable(borgerlang src/main.cpp)

# Find the LLVM libraries that correspond to required LLVM components
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link to LLVM libraries
target_link_libraries(borgerlang LLVM)