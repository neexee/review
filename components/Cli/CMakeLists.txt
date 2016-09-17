cmake_minimum_required(VERSION 3.0)

project(Cli CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(${PROJECT_NAME}_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE STRING "CLI include directory")

include_directories(${Cli_INCLUDE_DIR}
					${Utils_INCLUDE_DIR}
					${Git_INCLUDE_DIR})

file(GLOB CPP_FILES src/*.cpp)
file(GLOB HEADER_FILES include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} Git ${Boost_LIBRARIES})
