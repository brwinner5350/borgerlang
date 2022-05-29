cmake_minimum_required(VERSION 3.10)

# Project name
project(borgerlang)

find_package(LLVM REQUIRED CONFIG)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Includes & definitions
include_directories(${LLVM_INCLUDE_DIRS} include build)
add_definitions(${LLVM_DEFINITIONS})

flex_target(lexer src/tokens.l "${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp")
bison_target(parser src/parser.y "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp")

add_flex_bison_dependency(lexer parser)

# Borgerlang compiler executable
add_executable(borgerlang src/main.cpp src/codegen.cpp src/corefuncs.cpp
    "${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp")

# Find the LLVM libraries that correspond to required LLVM components
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link to LLVM libraries
target_link_libraries(borgerlang LLVM)