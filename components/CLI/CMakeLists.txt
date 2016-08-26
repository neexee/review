cmake_minimum_required(VERSION 3.0)

project(Cli CXX)
set(CMAKE_CXX_STANDARD 14)

include_directories(${Git_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}/include)


set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
                                 ${Git_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(${PROJECT_NAME}_DEFINITIONS ${PROJECT_SOURCE_DIR}/include
                                ${GIT_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)

file(GLOB HEADER_FILES include/*.h)
file(GLOB CPP_FILES src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} Git)
