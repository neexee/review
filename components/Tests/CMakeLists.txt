cmake_minimum_required(VERSION 3.0)

project(tests CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(${PROJECT_NAME}_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE STRING "Tests include directory")

include_directories(${tests_INCLUDE_DIR}
					${Cli_INCLUDE_DIR}
					${Git_INCLUDE_DIR}
					${Utils_INCLUDE_DIR}
					${Review_INCLUDE_DIR})

file(GLOB CPP_FILES src/*.cpp)
file(GLOB HEADER_FILES include/Tests/*.h)

add_executable(${PROJECT_NAME} ${CPP_FILES})
add_dependencies(${PROJECT_NAME} Cli Git Review Utils)

target_link_libraries(${PROJECT_NAME} Cli Git Review Utils gtest)
