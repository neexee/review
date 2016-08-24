cmake_minimum_required(VERSION 3.0)

project(review CXX)
set(CMAKE_CXX_STANDARD 14)
include_directories(${Cli_INCLUDE_DIRS})

file(GLOB CPP_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${CPP_FILES})
target_link_libraries(${PROJECT_NAME} Cli)
