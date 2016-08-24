cmake_minimum_required(VERSION 3.0)

project(Git CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

include("${PROJECT_SOURCE_DIR}/cmake/FindLibGit2.cmake")
add_definitions(${LIBGIT2_DEFINITIONS})

include_directories(${Utils_INCLUDE_DIRS}
                    ${LIBGIT2_INCLUDE_DIRS}
                    include)

file(GLOB CPP_FILES src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} Utils ${LIBGIT2_LIBRARIES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
                                 ${Utils_INCLUDE_DIRS}
                                 ${LIBGIT2_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(${PROJECT_NAME}_DEFINITIONS ${LIBGIT2_DEFINITIONS}
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)
