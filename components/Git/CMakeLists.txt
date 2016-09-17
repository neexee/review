cmake_minimum_required(VERSION 3.0)

project(Git CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(${PROJECT_NAME}_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include CACHE STRING "Git include directory")

include_directories(
    ${Git_INCLUDE_DIR}
    ${Utils_INCLUDE_DIR}
    ${LIBGIT2_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include("${PROJECT_SOURCE_DIR}/cmake/FindLibGit2.cmake")
add_definitions(${LIBGIT2_DEFINITIONS})

file(GLOB CPP_FILES src/*.cpp)
file(GLOB HEADER_FILES include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} Utils ${LIBGIT2_LIBRARIES})
