cmake_minimum_required(VERSION 3.0)

project(Utils CXX)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.60.0 COMPONENTS system filesystem REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${Boost_INCLUDE_DIRS})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
                                 ${Boost_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

file(GLOB HEADER_FILES include/*.h)
file(GLOB CPP_FILES src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
