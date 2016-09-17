cmake_minimum_required(VERSION 3.0)

project(Utils CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

find_package(Boost 1.60.0 COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(${PROJECT_NAME}_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include CACHE STRING "Utils include directory")

include_directories(
    ${Utils_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR})

file(GLOB CPP_FILES src/*.cpp)
file(GLOB HEADER_FILES include/${PROJECT_NAME}/*.h)

add_library(Utils STATIC ${CPP_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})